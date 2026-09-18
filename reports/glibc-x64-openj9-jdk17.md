---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:28:25 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 385 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1789712629 15
1789712634 15
1789712639 15
1789712644 15
1789712649 15
1789712654 15
1789712659 15
1789712664 17
1789712669 17
1789712674 17
1789712679 17
1789712684 17
1789712689 17
1789712694 17
1789712699 17
1789712704 17
1789712709 17
1789712714 17
1789712719 17
1789712724 17
```
</details>

---

