---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:38:23 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795001582 38
1795001587 38
1795001592 38
1795001597 38
1795001602 38
1795001607 38
1795001612 38
1795001617 38
1795001622 38
1795001627 38
1795001632 38
1795001637 38
1795001642 38
1795001647 38
1795001652 38
1795001657 38
1795001662 38
1795001667 38
1795001672 33
1795001677 33
```
</details>

---

