---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 08:57:43 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1793019082 55
1793019087 55
1793019092 55
1793019097 55
1793019102 57
1793019107 57
1793019112 57
1793019117 57
1793019122 57
1793019127 57
1793019132 57
1793019137 57
1793019142 57
1793019147 57
1793019152 57
1793019157 57
1793019162 57
1793019167 57
1793019172 57
1793019177 57
```
</details>

---

