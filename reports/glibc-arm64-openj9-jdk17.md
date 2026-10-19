---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-18 21:26:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792372851 46
1792372856 46
1792372861 46
1792372866 46
1792372872 46
1792372877 46
1792372882 46
1792372887 46
1792372892 46
1792372897 46
1792372902 48
1792372907 48
1792372912 48
1792372917 48
1792372922 48
1792372927 48
1792372932 48
1792372937 48
1792372942 48
1792372947 48
```
</details>

---

