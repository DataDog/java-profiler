---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:13:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 62-73 cores)</summary>

```
1795194475 66
1795194480 66
1795194485 66
1795194490 66
1795194495 64
1795194500 64
1795194505 64
1795194510 64
1795194515 64
1795194520 64
1795194525 62
1795194530 62
1795194535 62
1795194540 62
1795194545 62
1795194550 62
1795194555 62
1795194560 62
1795194565 62
1795194570 62
```
</details>

---

