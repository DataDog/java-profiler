---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
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
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793830730 30
1793830735 30
1793830740 30
1793830745 30
1793830750 30
1793830755 30
1793830760 30
1793830765 32
1793830770 32
1793830775 32
1793830780 32
1793830785 32
1793830790 32
1793830795 32
1793830800 32
1793830805 32
1793830810 32
1793830815 32
1793830820 32
1793830825 32
```
</details>

---

