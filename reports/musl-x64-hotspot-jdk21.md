---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:38:17 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 964 |
| Sample Rate | 16.07/sec |
| Health Score | 1004% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (6 unique values: 85-92 cores)</summary>

```
1794479530 89
1794479535 87
1794479540 87
1794479545 87
1794479550 87
1794479555 87
1794479560 85
1794479565 85
1794479570 85
1794479575 88
1794479580 88
1794479585 88
1794479590 88
1794479595 88
1794479601 88
1794479606 92
1794479611 92
1794479616 92
1794479621 92
1794479626 92
```
</details>

---

