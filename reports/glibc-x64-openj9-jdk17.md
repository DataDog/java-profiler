---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-26 09:45:33 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 10 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 77-96 cores)</summary>

```
1787751619 77
1787751624 77
1787751629 77
1787751634 77
1787751639 77
1787751644 77
1787751649 77
1787751654 77
1787751659 77
1787751664 79
1787751669 79
1787751674 79
1787751679 79
1787751684 79
1787751689 79
1787751694 79
1787751699 79
1787751704 96
1787751709 96
1787751714 96
```
</details>

---

