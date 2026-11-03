---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:22:17 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1793722600 63
1793722605 65
1793722610 65
1793722615 65
1793722620 65
1793722625 65
1793722630 65
1793722635 63
1793722640 63
1793722645 63
1793722650 63
1793722655 63
1793722660 63
1793722665 63
1793722670 63
1793722675 63
1793722680 63
1793722685 63
1793722690 63
1793722695 63
```
</details>

---

