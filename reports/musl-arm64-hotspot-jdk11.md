---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:30:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 41-64 cores)</summary>

```
1794943484 46
1794943489 46
1794943494 41
1794943499 41
1794943504 41
1794943509 41
1794943514 41
1794943519 41
1794943524 41
1794943529 41
1794943534 41
1794943539 41
1794943544 41
1794943549 41
1794943554 46
1794943559 46
1794943564 51
1794943569 51
1794943574 51
1794943579 51
```
</details>

---

