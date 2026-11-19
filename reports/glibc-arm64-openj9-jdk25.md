---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:10:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 11 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 14 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 30-36 cores)</summary>

```
1795129618 30
1795129623 30
1795129628 30
1795129633 30
1795129638 30
1795129643 30
1795129648 30
1795129653 30
1795129658 30
1795129663 30
1795129668 30
1795129674 30
1795129679 30
1795129684 36
1795129689 36
1795129694 36
1795129699 36
1795129704 36
1795129709 36
1795129714 36
```
</details>

---

