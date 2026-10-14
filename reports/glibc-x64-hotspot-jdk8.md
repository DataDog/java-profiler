---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-14 10:47:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 38-42 cores)</summary>

```
1791988867 40
1791988872 40
1791988877 42
1791988882 42
1791988887 42
1791988892 42
1791988897 42
1791988902 42
1791988907 42
1791988912 38
1791988917 38
1791988922 38
1791988927 38
1791988932 38
1791988937 38
1791988942 38
1791988947 38
1791988952 38
1791988957 38
1791988962 38
```
</details>

---

