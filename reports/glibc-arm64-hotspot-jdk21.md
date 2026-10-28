---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:48:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 35-39 cores)</summary>

```
1793187922 39
1793187927 39
1793187932 39
1793187937 39
1793187942 39
1793187947 39
1793187952 39
1793187957 39
1793187962 39
1793187967 39
1793187973 39
1793187978 39
1793187983 39
1793187988 39
1793187993 39
1793187998 39
1793188003 39
1793188008 35
1793188013 35
1793188018 35
```
</details>

---

