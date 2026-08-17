---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 11:56:10 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 72-80 cores)</summary>

```
1786981948 80
1786981953 80
1786981958 80
1786981963 80
1786981968 80
1786981973 80
1786981978 80
1786981983 72
1786981988 72
1786981993 72
1786981998 72
1786982003 72
1786982008 72
1786982013 72
1786982018 72
1786982023 72
1786982028 72
1786982033 72
1786982038 72
1786982043 72
```
</details>

---

