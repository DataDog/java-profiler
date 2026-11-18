---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:29:50 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 25-29 cores)</summary>

```
1795001032 29
1795001037 29
1795001042 25
1795001047 25
1795001052 25
1795001057 25
1795001062 25
1795001067 25
1795001072 25
1795001077 25
1795001082 25
1795001087 25
1795001092 25
1795001097 25
1795001102 25
1795001107 25
1795001112 25
1795001117 25
1795001122 25
1795001127 25
```
</details>

---

