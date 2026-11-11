---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:35:23 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 12 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1794396664 87
1794396669 87
1794396674 87
1794396679 87
1794396684 87
1794396689 87
1794396694 87
1794396699 87
1794396704 87
1794396709 89
1794396714 89
1794396719 87
1794396724 87
1794396729 87
1794396734 87
1794396739 85
1794396744 85
1794396749 85
1794396754 85
1794396759 85
```
</details>

---

