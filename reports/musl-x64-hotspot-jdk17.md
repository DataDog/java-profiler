---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 01:05:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793163614 62
1793163619 62
1793163624 64
1793163629 64
1793163634 64
1793163639 64
1793163644 64
1793163649 64
1793163654 64
1793163659 64
1793163664 64
1793163669 64
1793163674 64
1793163679 64
1793163684 64
1793163689 64
1793163694 64
1793163699 64
1793163704 64
1793163709 64
```
</details>

---

