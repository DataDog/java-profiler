---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:26:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1794406952 77
1794406957 77
1794406962 77
1794406967 77
1794406972 77
1794406977 77
1794406982 77
1794406987 77
1794406992 77
1794406997 77
1794407002 77
1794407007 77
1794407012 77
1794407017 77
1794407022 77
1794407027 77
1794407032 79
1794407037 79
1794407042 79
1794407047 75
```
</details>

---

