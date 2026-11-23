---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795434612 44
1795434617 44
1795434622 44
1795434627 44
1795434632 49
1795434637 49
1795434642 49
1795434647 49
1795434652 49
1795434657 49
1795434662 49
1795434667 49
1795434672 49
1795434677 49
1795434682 49
1795434687 49
1795434692 49
1795434697 49
1795434702 49
1795434707 49
```
</details>

---

