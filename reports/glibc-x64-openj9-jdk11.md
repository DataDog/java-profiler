---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:27:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 59-79 cores)</summary>

```
1794572485 59
1794572490 59
1794572495 59
1794572500 59
1794572505 59
1794572510 63
1794572515 63
1794572520 63
1794572525 63
1794572530 63
1794572535 63
1794572540 63
1794572545 79
1794572550 79
1794572555 79
1794572560 79
1794572565 79
1794572570 79
1794572575 79
1794572580 79
```
</details>

---

