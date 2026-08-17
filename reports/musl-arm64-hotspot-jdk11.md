---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 12:12:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 8 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786982786 46
1786982791 46
1786982796 46
1786982801 46
1786982806 46
1786982811 46
1786982816 46
1786982821 46
1786982826 46
1786982831 46
1786982836 48
1786982841 48
1786982846 48
1786982851 48
1786982856 48
1786982861 48
1786982866 48
1786982871 48
1786982876 48
1786982881 48
```
</details>

---

