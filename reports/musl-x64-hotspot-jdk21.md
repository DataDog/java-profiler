---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 05:58:33 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1793789565 94
1793789570 94
1793789575 94
1793789580 94
1793789585 92
1793789590 92
1793789595 92
1793789600 92
1793789605 92
1793789610 92
1793789615 92
1793789620 92
1793789625 92
1793789630 92
1793789635 92
1793789640 92
1793789645 92
1793789650 92
1793789655 92
1793789660 92
```
</details>

---

