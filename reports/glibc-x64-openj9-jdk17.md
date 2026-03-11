---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 14:07:38 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 52-61 cores)</summary>

```
1773252124 52
1773252129 52
1773252134 52
1773252139 52
1773252144 52
1773252149 52
1773252154 52
1773252159 52
1773252164 52
1773252169 52
1773252174 57
1773252179 57
1773252184 57
1773252189 55
1773252194 55
1773252199 57
1773252204 57
1773252209 57
1773252214 57
1773252219 57
```
</details>

---

