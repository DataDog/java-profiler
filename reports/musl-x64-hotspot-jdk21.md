---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:13:41 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 73-79 cores)</summary>

```
1795194485 79
1795194490 79
1795194495 79
1795194500 79
1795194505 79
1795194510 79
1795194515 79
1795194520 79
1795194525 79
1795194530 79
1795194535 79
1795194540 79
1795194545 76
1795194550 76
1795194555 76
1795194560 76
1795194565 76
1795194570 73
1795194575 73
1795194580 73
```
</details>

---

