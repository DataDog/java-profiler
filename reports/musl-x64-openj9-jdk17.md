---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 14:06:10 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1007 |
| Sample Rate | 16.78/sec |
| Health Score | 1049% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 38-60 cores)</summary>

```
1790272861 38
1790272866 38
1790272871 38
1790272876 38
1790272881 38
1790272887 38
1790272892 60
1790272897 60
1790272902 40
1790272907 40
1790272912 40
1790272917 40
1790272922 40
1790272927 40
1790272932 40
1790272937 40
1790272942 40
1790272947 40
1790272952 40
1790272957 40
```
</details>

---

