---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:15:11 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 12 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (4 unique values: 28-50 cores)</summary>

```
1795194629 50
1795194634 50
1795194639 50
1795194644 50
1795194649 50
1795194654 50
1795194659 50
1795194664 50
1795194669 50
1795194674 50
1795194679 50
1795194684 50
1795194689 50
1795194694 50
1795194699 50
1795194704 50
1795194709 50
1795194714 50
1795194719 45
1795194724 45
```
</details>

---

