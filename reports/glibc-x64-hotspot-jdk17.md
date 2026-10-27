---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 20:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793061937 32
1793061942 28
1793061947 28
1793061952 28
1793061957 28
1793061962 28
1793061967 28
1793061972 30
1793061977 30
1793061982 30
1793061987 30
1793061992 30
1793061997 30
1793062002 30
1793062007 30
1793062012 30
1793062017 30
1793062023 30
1793062028 30
1793062033 30
```
</details>

---

