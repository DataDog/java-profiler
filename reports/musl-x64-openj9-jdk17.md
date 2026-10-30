---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 09:50:47 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 60-70 cores)</summary>

```
1793367972 62
1793367977 62
1793367982 60
1793367987 60
1793367992 60
1793367997 60
1793368002 60
1793368007 60
1793368012 60
1793368017 60
1793368023 60
1793368028 60
1793368033 60
1793368038 60
1793368043 60
1793368048 60
1793368053 60
1793368058 60
1793368063 60
1793368068 62
```
</details>

---

