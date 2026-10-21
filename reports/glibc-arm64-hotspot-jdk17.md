---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 08:20:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 9 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1792584877 40
1792584882 40
1792584887 40
1792584892 40
1792584897 40
1792584902 40
1792584907 40
1792584912 40
1792584917 40
1792584922 40
1792584927 40
1792584932 40
1792584937 40
1792584942 40
1792584947 40
1792584952 40
1792584957 40
1792584962 40
1792584967 40
1792584972 40
```
</details>

---

