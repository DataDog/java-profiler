---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 11 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1795705990 62
1795705996 64
1795706001 64
1795706006 64
1795706011 64
1795706016 64
1795706021 64
1795706026 64
1795706031 64
1795706036 64
1795706041 64
1795706046 64
1795706051 64
1795706056 64
1795706061 64
1795706066 64
1795706071 66
1795706076 66
1795706081 66
1795706086 66
```
</details>

---

