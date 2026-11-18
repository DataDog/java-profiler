---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:20:02 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1795014931 73
1795014936 73
1795014941 73
1795014946 73
1795014951 73
1795014956 73
1795014961 75
1795014966 75
1795014971 75
1795014976 75
1795014981 75
1795014986 75
1795014991 75
1795014996 75
1795015001 75
1795015006 75
1795015011 81
1795015016 81
1795015021 81
1795015026 81
```
</details>

---

