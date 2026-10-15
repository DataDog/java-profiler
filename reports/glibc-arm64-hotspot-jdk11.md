---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 17:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1115 |
| Sample Rate | 18.58/sec |
| Health Score | 1161% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
1792100859 34
1792100864 34
1792100869 34
1792100874 34
1792100879 34
1792100884 51
1792100889 51
1792100894 51
1792100899 51
1792100904 51
1792100909 51
1792100914 46
1792100919 46
1792100924 46
1792100929 46
1792100934 46
1792100939 46
1792100944 46
1792100949 46
1792100954 46
```
</details>

---

