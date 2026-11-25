---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:17:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 32-55 cores)</summary>

```
1795605129 55
1795605134 55
1795605139 46
1795605144 46
1795605149 46
1795605154 46
1795605159 37
1795605164 37
1795605169 37
1795605174 37
1795605179 34
1795605184 34
1795605189 32
1795605194 32
1795605199 32
1795605204 32
1795605209 32
1795605214 32
1795605219 32
1795605224 32
```
</details>

---

