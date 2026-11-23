---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:55:22 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 61-66 cores)</summary>

```
1795434627 61
1795434632 61
1795434637 61
1795434642 61
1795434647 61
1795434652 61
1795434657 61
1795434662 61
1795434667 64
1795434672 64
1795434677 64
1795434682 64
1795434687 64
1795434692 64
1795434697 64
1795434702 64
1795434707 66
1795434712 66
1795434717 66
1795434722 66
```
</details>

---

