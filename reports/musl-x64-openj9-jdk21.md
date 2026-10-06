---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 11:23:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1791299912 9
1791299917 9
1791299922 9
1791299927 9
1791299932 9
1791299937 9
1791299942 11
1791299947 11
1791299952 9
1791299957 9
1791299962 9
1791299967 9
1791299972 11
1791299977 11
1791299982 11
1791299987 11
1791299992 11
1791299997 11
1791300002 11
1791300007 11
```
</details>

---

