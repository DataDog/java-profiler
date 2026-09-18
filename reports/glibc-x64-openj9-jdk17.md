---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:29:44 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 40-76 cores)</summary>

```
1789712730 76
1789712735 76
1789712740 76
1789712745 76
1789712750 76
1789712755 76
1789712760 76
1789712765 76
1789712770 76
1789712775 76
1789712780 76
1789712785 76
1789712790 40
1789712795 40
1789712800 40
1789712805 40
1789712810 40
1789712815 40
1789712820 40
1789712825 40
```
</details>

---

