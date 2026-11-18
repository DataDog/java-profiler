---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 08:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-41 cores)</summary>

```
1795007912 36
1795007917 36
1795007922 36
1795007927 36
1795007932 36
1795007937 36
1795007942 36
1795007947 36
1795007952 36
1795007957 36
1795007962 39
1795007967 39
1795007972 39
1795007977 39
1795007982 39
1795007987 39
1795007992 39
1795007997 39
1795008002 39
1795008007 39
```
</details>

---

