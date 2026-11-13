---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:40:55 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 8 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 51-73 cores)</summary>

```
1794573228 71
1794573233 71
1794573238 71
1794573243 71
1794573248 71
1794573253 71
1794573258 71
1794573263 71
1794573268 71
1794573273 71
1794573278 71
1794573283 71
1794573288 71
1794573293 71
1794573298 71
1794573303 71
1794573308 71
1794573313 71
1794573318 73
1794573323 73
```
</details>

---

