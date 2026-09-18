---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 05:01:28 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (4 unique values: 37-47 cores)</summary>

```
1789721678 37
1789721683 37
1789721688 37
1789721693 37
1789721698 37
1789721703 37
1789721708 39
1789721713 39
1789721718 39
1789721723 39
1789721728 37
1789721733 37
1789721738 37
1789721743 37
1789721748 45
1789721753 45
1789721758 45
1789721763 45
1789721768 45
1789721773 45
```
</details>

---

