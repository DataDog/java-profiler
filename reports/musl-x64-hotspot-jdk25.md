---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 10:36:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793370641 30
1793370646 32
1793370651 32
1793370656 32
1793370661 32
1793370666 32
1793370671 32
1793370676 32
1793370681 32
1793370686 32
1793370691 32
1793370696 32
1793370701 32
1793370706 32
1793370711 32
1793370716 32
1793370721 32
1793370726 32
1793370731 32
1793370736 32
```
</details>

---

