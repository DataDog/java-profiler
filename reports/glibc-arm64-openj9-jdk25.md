---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 00:07:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1793855048 35
1793855053 35
1793855058 35
1793855063 35
1793855068 35
1793855073 35
1793855078 35
1793855083 35
1793855088 35
1793855093 35
1793855098 35
1793855103 35
1793855108 35
1793855113 35
1793855118 35
1793855123 35
1793855128 35
1793855133 35
1793855138 40
1793855143 40
```
</details>

---

