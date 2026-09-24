---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 16:31:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 984 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 56-70 cores)</summary>

```
1790281556 68
1790281561 68
1790281566 68
1790281571 68
1790281576 68
1790281581 70
1790281586 70
1790281591 70
1790281596 70
1790281601 70
1790281606 58
1790281611 58
1790281616 56
1790281621 56
1790281626 56
1790281631 56
1790281636 56
1790281641 56
1790281646 56
1790281651 56
```
</details>

---

