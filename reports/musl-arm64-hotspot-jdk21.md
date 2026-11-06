---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-06 07:08:28 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 38-43 cores)</summary>

```
1793966632 41
1793966637 41
1793966642 41
1793966647 41
1793966652 41
1793966657 38
1793966662 38
1793966667 38
1793966672 38
1793966677 42
1793966682 42
1793966687 42
1793966692 42
1793966697 42
1793966702 42
1793966707 43
1793966712 43
1793966717 41
1793966722 41
1793966727 41
```
</details>

---

