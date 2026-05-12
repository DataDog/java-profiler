---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 28-36 cores)</summary>

```
1778582450 36
1778582455 36
1778582460 36
1778582465 36
1778582470 36
1778582475 36
1778582480 36
1778582485 36
1778582490 36
1778582495 36
1778582500 36
1778582505 36
1778582510 36
1778582515 36
1778582520 36
1778582525 28
1778582530 28
1778582535 28
1778582540 28
1778582545 28
```
</details>

---

