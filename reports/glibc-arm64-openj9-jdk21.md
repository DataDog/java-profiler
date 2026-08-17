---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 12:12:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1786982786 9
1786982791 9
1786982796 9
1786982801 9
1786982806 9
1786982811 9
1786982816 9
1786982821 9
1786982826 9
1786982831 14
1786982836 14
1786982841 14
1786982846 14
1786982851 14
1786982856 14
1786982861 14
1786982866 14
1786982871 14
1786982876 14
1786982881 14
```
</details>

---

