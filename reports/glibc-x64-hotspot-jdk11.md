---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 16:58:41 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 37-63 cores)</summary>

```
1792615977 37
1792615982 37
1792615987 37
1792615992 37
1792615997 37
1792616002 37
1792616007 37
1792616012 37
1792616017 37
1792616022 37
1792616027 37
1792616032 37
1792616037 37
1792616042 37
1792616047 37
1792616052 37
1792616057 37
1792616062 37
1792616067 37
1792616072 63
```
</details>

---

