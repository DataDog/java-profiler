---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:28:41 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (4 unique values: 65-74 cores)</summary>

```
1795796621 69
1795796626 69
1795796631 69
1795796636 69
1795796641 74
1795796646 74
1795796651 74
1795796656 74
1795796661 65
1795796666 65
1795796671 65
1795796676 65
1795796681 65
1795796686 65
1795796691 67
1795796696 67
1795796701 67
1795796706 67
1795796711 67
1795796716 69
```
</details>

---

