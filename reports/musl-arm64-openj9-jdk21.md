---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 07:23:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 827 |
| Sample Rate | 13.78/sec |
| Health Score | 861% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 45-53 cores)</summary>

```
1790853549 53
1790853554 53
1790853559 53
1790853564 53
1790853569 53
1790853574 53
1790853579 53
1790853584 53
1790853589 53
1790853594 53
1790853599 45
1790853604 45
1790853609 45
1790853614 45
1790853619 45
1790853624 45
1790853629 45
1790853634 45
1790853639 45
1790853644 45
```
</details>

---

