---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 13:24:30 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 31-43 cores)</summary>

```
1791220803 43
1791220808 43
1791220813 43
1791220818 43
1791220823 43
1791220828 43
1791220833 43
1791220838 43
1791220843 31
1791220848 31
1791220853 31
1791220858 31
1791220863 31
1791220868 31
1791220873 31
1791220878 31
1791220883 31
1791220888 31
1791220893 31
1791220898 31
```
</details>

---

