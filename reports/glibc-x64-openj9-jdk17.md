---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 07:44:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791891535 32
1791891540 32
1791891545 32
1791891550 32
1791891555 32
1791891560 32
1791891565 32
1791891570 32
1791891575 32
1791891580 32
1791891585 30
1791891590 30
1791891595 30
1791891600 30
1791891605 30
1791891610 30
1791891615 30
1791891620 30
1791891625 30
1791891630 30
```
</details>

---

