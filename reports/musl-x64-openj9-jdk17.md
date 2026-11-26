---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:25:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 24-34 cores)</summary>

```
1795702822 27
1795702827 27
1795702832 27
1795702837 27
1795702842 27
1795702847 27
1795702852 27
1795702857 27
1795702862 27
1795702867 27
1795702872 27
1795702877 27
1795702882 27
1795702887 27
1795702892 29
1795702897 29
1795702902 24
1795702907 24
1795702912 24
1795702917 31
```
</details>

---

