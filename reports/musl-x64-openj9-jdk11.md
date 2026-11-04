---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 03:32:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 56-78 cores)</summary>

```
1793780907 78
1793780912 78
1793780917 56
1793780922 56
1793780927 56
1793780932 56
1793780937 56
1793780942 56
1793780947 56
1793780952 56
1793780957 56
1793780962 56
1793780967 56
1793780972 56
1793780977 56
1793780982 56
1793780987 56
1793780992 56
1793780997 56
1793781002 56
```
</details>

---

