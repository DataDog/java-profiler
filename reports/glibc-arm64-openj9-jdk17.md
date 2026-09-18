---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:28:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1789712670 19
1789712675 19
1789712680 19
1789712685 24
1789712690 24
1789712695 24
1789712700 24
1789712705 24
1789712710 24
1789712715 29
1789712720 29
1789712725 29
1789712730 29
1789712735 29
1789712740 29
1789712745 29
1789712750 29
1789712755 29
1789712760 29
1789712765 24
```
</details>

---

