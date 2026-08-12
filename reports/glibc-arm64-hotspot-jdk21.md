---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 11:23:57 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (6 unique values: 32-44 cores)</summary>

```
1786547872 43
1786547877 44
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
```
</details>

---

