---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 09:45:33 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787751618 66
1787751623 66
1787751628 66
1787751633 66
1787751638 66
1787751643 66
1787751648 66
1787751653 66
1787751658 64
1787751663 64
1787751668 64
1787751673 64
1787751678 64
1787751683 64
1787751688 64
1787751693 64
1787751698 64
1787751703 64
1787751708 66
1787751713 66
```
</details>

---

