---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 55-63 cores)</summary>

```
1777983470 63
1777983475 63
1777983480 63
1777983485 63
1777983490 63
1777983495 60
1777983500 60
1777983505 60
1777983510 60
1777983515 60
1777983520 60
1777983525 60
1777983530 60
1777983535 60
1777983540 60
1777983545 60
1777983550 60
1777983555 60
1777983560 60
1777983565 60
```
</details>

---

