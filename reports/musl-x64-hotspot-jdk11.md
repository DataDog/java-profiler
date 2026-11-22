---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 15:36:12 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 33-66 cores)</summary>

```
1795379505 33
1795379510 33
1795379515 33
1795379520 33
1795379525 66
1795379530 66
1795379535 66
1795379540 66
1795379545 66
1795379550 66
1795379555 66
1795379560 66
1795379565 66
1795379570 66
1795379575 66
1795379580 66
1795379586 66
1795379591 66
1795379596 66
1795379601 66
```
</details>

---

