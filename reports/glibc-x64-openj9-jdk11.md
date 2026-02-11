---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:40:58 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (7 unique values: 45-61 cores)</summary>

```
1770827500 47
1770827505 47
1770827510 47
1770827515 45
1770827520 45
1770827525 50
1770827530 50
1770827535 50
1770827540 55
1770827545 55
1770827550 59
1770827555 59
1770827560 59
1770827565 61
1770827570 61
1770827575 59
1770827580 59
1770827585 59
1770827590 59
1770827595 59
```
</details>

---

