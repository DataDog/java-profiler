---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:23:43 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 57-63 cores)</summary>

```
1790853524 59
1790853529 59
1790853534 59
1790853539 59
1790853544 59
1790853549 59
1790853554 61
1790853559 61
1790853564 61
1790853569 61
1790853574 61
1790853579 61
1790853584 61
1790853589 63
1790853594 63
1790853599 63
1790853604 57
1790853609 57
1790853614 57
1790853619 57
```
</details>

---

