---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 05:49:04 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1789983807 44
1789983812 44
1789983817 44
1789983823 44
1789983828 44
1789983833 44
1789983838 44
1789983843 44
1789983848 44
1789983853 44
1789983858 48
1789983863 48
1789983868 48
1789983873 48
1789983878 48
1789983883 48
1789983888 48
1789983893 48
1789983898 48
1789983903 48
```
</details>

---

