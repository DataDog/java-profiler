---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 01:04:37 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 7 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1786337947 32
1786337952 34
1786337957 34
1786337962 34
1786337967 34
1786337972 34
1786337977 34
1786337982 34
1786337987 34
1786337992 34
1786337997 34
1786338002 34
1786338007 34
1786338012 34
1786338017 34
1786338022 34
1786338027 34
1786338032 34
1786338037 34
1786338042 34
```
</details>

---

