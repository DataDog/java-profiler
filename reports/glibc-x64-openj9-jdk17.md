---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 08:55:33 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1792759872 74
1792759877 74
1792759882 74
1792759887 74
1792759892 74
1792759897 74
1792759902 74
1792759907 74
1792759912 74
1792759917 74
1792759922 74
1792759927 74
1792759932 74
1792759937 74
1792759942 74
1792759947 72
1792759952 72
1792759957 72
1792759962 72
1792759967 72
```
</details>

---

