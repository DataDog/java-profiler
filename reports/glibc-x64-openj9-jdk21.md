---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:17:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 34-49 cores)</summary>

```
1795605129 49
1795605134 49
1795605139 49
1795605144 49
1795605149 46
1795605154 46
1795605159 46
1795605164 46
1795605169 41
1795605174 41
1795605179 43
1795605184 43
1795605189 43
1795605194 43
1795605199 43
1795605204 43
1795605209 43
1795605214 43
1795605219 43
1795605224 43
```
</details>

---

