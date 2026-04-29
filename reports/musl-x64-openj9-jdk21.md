---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 07:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 54 |
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
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 41-56 cores)</summary>

```
1777462480 41
1777462485 41
1777462490 41
1777462495 41
1777462500 41
1777462505 41
1777462510 41
1777462515 41
1777462520 41
1777462525 56
1777462530 56
1777462535 56
1777462540 56
1777462545 56
1777462550 56
1777462555 54
1777462560 54
1777462565 54
1777462570 54
1777462575 54
```
</details>

---

