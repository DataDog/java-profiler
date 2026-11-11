---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:26:45 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 7 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794406972 43
1794406977 43
1794406982 43
1794406987 43
1794406992 48
1794406997 48
1794407002 48
1794407007 48
1794407013 48
1794407018 48
1794407023 48
1794407028 48
1794407033 48
1794407038 48
1794407043 48
1794407048 48
1794407053 48
1794407058 48
1794407063 48
1794407068 48
```
</details>

---

