---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:07:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (6 unique values: 41-51 cores)</summary>

```
1793372546 41
1793372551 41
1793372556 41
1793372561 41
1793372566 46
1793372571 46
1793372576 46
1793372581 46
1793372586 51
1793372591 51
1793372596 51
1793372601 51
1793372606 51
1793372611 51
1793372616 49
1793372621 49
1793372626 49
1793372631 44
1793372636 44
1793372641 44
```
</details>

---

