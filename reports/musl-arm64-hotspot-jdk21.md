---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 12:58:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (4 unique values: 29-51 cores)</summary>

```
1794592498 51
1794592504 51
1794592509 46
1794592514 46
1794592519 46
1794592524 46
1794592529 46
1794592534 46
1794592539 34
1794592544 34
1794592549 34
1794592554 34
1794592559 34
1794592564 34
1794592569 34
1794592574 34
1794592579 29
1794592584 29
1794592589 29
1794592594 29
```
</details>

---

