---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 09:26:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787318494 88
1787318499 88
1787318504 88
1787318509 88
1787318514 88
1787318519 88
1787318524 88
1787318529 88
1787318534 88
1787318539 88
1787318544 88
1787318549 88
1787318554 88
1787318559 88
1787318564 88
1787318569 88
1787318574 88
1787318579 88
1787318584 88
1787318589 96
```
</details>

---

