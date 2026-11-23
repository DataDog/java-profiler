---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795434627 44
1795434632 44
1795434637 44
1795434642 49
1795434647 49
1795434652 49
1795434657 49
1795434662 49
1795434667 49
1795434672 44
1795434677 44
1795434682 44
1795434687 44
1795434692 44
1795434697 44
1795434702 44
1795434707 44
1795434712 44
1795434717 44
1795434722 44
```
</details>

---

