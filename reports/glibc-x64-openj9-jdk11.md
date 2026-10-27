---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 17:57:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 76-94 cores)</summary>

```
1793137980 76
1793137985 76
1793137990 76
1793137995 76
1793138000 92
1793138005 92
1793138010 92
1793138015 92
1793138020 92
1793138025 92
1793138030 92
1793138035 92
1793138040 89
1793138045 89
1793138050 89
1793138055 89
1793138060 89
1793138065 89
1793138070 89
1793138075 89
```
</details>

---

