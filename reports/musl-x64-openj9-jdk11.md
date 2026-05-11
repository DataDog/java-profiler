---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 18:32:12 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1191 |
| Sample Rate | 19.85/sec |
| Health Score | 1241% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 71-76 cores)</summary>

```
1778538455 71
1778538460 71
1778538465 71
1778538470 71
1778538475 71
1778538480 71
1778538485 71
1778538490 71
1778538495 71
1778538500 76
1778538505 76
1778538510 76
1778538515 76
1778538520 76
1778538525 76
1778538530 76
1778538535 76
1778538540 76
1778538545 76
1778538550 76
```
</details>

---

