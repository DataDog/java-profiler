---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 11:23:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (5 unique values: 32-44 cores)</summary>

```
1786547882 44
1786547887 42
1786547892 42
1786547897 42
1786547902 42
1786547907 42
1786547912 42
1786547917 42
1786547922 42
1786547927 42
1786547932 42
1786547937 42
1786547942 42
1786547947 42
1786547952 37
1786547957 37
1786547962 32
1786547967 32
1786547972 32
1786547977 32
```
</details>

---

