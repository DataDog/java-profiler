---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 08:19:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 71-75 cores)</summary>

```
1790856877 71
1790856882 71
1790856887 71
1790856892 71
1790856897 73
1790856902 73
1790856907 73
1790856912 73
1790856917 73
1790856922 75
1790856927 75
1790856932 75
1790856937 75
1790856942 75
1790856947 75
1790856952 75
1790856957 75
1790856962 75
1790856967 75
1790856972 75
```
</details>

---

