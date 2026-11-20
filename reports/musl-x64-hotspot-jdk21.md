---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 10:50:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (6 unique values: 72-84 cores)</summary>

```
1795189577 72
1795189582 72
1795189587 78
1795189592 78
1795189597 78
1795189602 78
1795189607 75
1795189612 75
1795189617 75
1795189622 75
1795189627 75
1795189632 84
1795189637 84
1795189642 84
1795189647 84
1795189652 84
1795189657 84
1795189662 84
1795189667 84
1795189672 84
```
</details>

---

