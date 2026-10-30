---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 10:36:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793370646 43
1793370651 43
1793370656 48
1793370661 48
1793370666 48
1793370671 48
1793370676 48
1793370681 48
1793370686 48
1793370691 48
1793370696 48
1793370701 48
1793370706 48
1793370711 48
1793370716 48
1793370721 48
1793370726 48
1793370731 48
1793370736 48
1793370741 48
```
</details>

---

