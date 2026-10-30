---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:47:21 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 30-36 cores)</summary>

```
1793374907 30
1793374912 30
1793374917 30
1793374922 30
1793374927 30
1793374932 30
1793374937 30
1793374942 30
1793374947 30
1793374952 30
1793374957 30
1793374962 30
1793374967 30
1793374972 30
1793374977 30
1793374982 30
1793374987 36
1793374992 36
1793374997 36
1793375002 36
```
</details>

---

