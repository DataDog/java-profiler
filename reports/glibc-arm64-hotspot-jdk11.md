---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:55:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795434627 64
1795434632 64
1795434637 64
1795434642 64
1795434647 64
1795434652 64
1795434657 64
1795434662 64
1795434667 64
1795434672 64
1795434677 64
1795434682 64
1795434687 64
1795434692 64
1795434697 64
1795434702 64
1795434707 64
1795434712 64
1795434717 64
1795434722 64
```
</details>

---

