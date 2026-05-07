---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 12:53:34 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 45-58 cores)</summary>

```
1778172541 54
1778172546 54
1778172551 54
1778172556 58
1778172561 58
1778172566 54
1778172571 54
1778172576 54
1778172581 54
1778172586 54
1778172591 54
1778172596 54
1778172601 54
1778172606 54
1778172611 54
1778172616 54
1778172621 54
1778172626 49
1778172631 49
1778172636 45
```
</details>

---

