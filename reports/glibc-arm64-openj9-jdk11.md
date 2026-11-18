---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:29:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795001058 64
1795001063 64
1795001068 64
1795001073 64
1795001078 64
1795001083 64
1795001088 64
1795001093 64
1795001098 64
1795001103 64
1795001108 64
1795001113 64
1795001118 64
1795001123 64
1795001128 64
1795001133 64
1795001138 64
1795001143 64
1795001148 64
1795001153 64
```
</details>

---

