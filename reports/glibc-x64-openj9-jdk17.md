---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:26:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794406962 93
1794406967 93
1794406972 93
1794406977 93
1794406982 93
1794406987 93
1794406992 93
1794406997 93
1794407002 93
1794407007 93
1794407012 91
1794407017 91
1794407022 91
1794407027 91
1794407032 91
1794407037 91
1794407042 91
1794407047 91
1794407052 91
1794407057 91
```
</details>

---

