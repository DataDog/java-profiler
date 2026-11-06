---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 10:29:01 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 850 |
| Sample Rate | 14.17/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1793978587 41
1793978592 41
1793978597 41
1793978602 41
1793978607 41
1793978612 41
1793978617 41
1793978622 41
1793978627 41
1793978632 41
1793978637 43
1793978642 43
1793978647 43
1793978652 43
1793978657 43
1793978662 43
1793978667 43
1793978672 43
1793978677 43
1793978682 43
```
</details>

---

