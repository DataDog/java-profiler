---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-18 21:27:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1792372897 96
1792372902 96
1792372907 96
1792372912 96
1792372917 96
1792372922 96
1792372927 96
1792372932 96
1792372937 96
1792372942 96
1792372947 96
1792372952 96
1792372957 96
1792372962 96
1792372967 96
1792372972 96
1792372977 96
1792372982 96
1792372987 96
1792372992 76
```
</details>

---

