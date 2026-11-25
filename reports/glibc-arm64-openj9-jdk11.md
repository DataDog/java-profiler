---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 09:53:37 EST

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795618091 64
1795618096 64
1795618102 64
1795618107 64
1795618112 64
1795618117 64
1795618122 64
1795618127 64
1795618132 64
1795618137 64
1795618142 64
1795618147 64
1795618152 64
1795618157 64
1795618162 64
1795618167 64
1795618172 64
1795618177 64
1795618182 64
1795618187 64
```
</details>

---

