---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 08:38:42 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 8 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 20-32 cores)</summary>

```
1770125671 20
1770125676 20
1770125681 20
1770125686 20
1770125691 20
1770125696 20
1770125701 20
1770125706 20
1770125711 20
1770125716 20
1770125721 32
1770125726 32
1770125731 30
1770125736 30
1770125741 30
1770125746 30
1770125751 30
1770125756 30
1770125761 30
1770125766 30
```
</details>

---

