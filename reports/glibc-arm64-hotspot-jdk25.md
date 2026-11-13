---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:40:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 9 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (5 unique values: 20-26 cores)</summary>

```
1794573223 22
1794573228 20
1794573233 20
1794573238 20
1794573243 20
1794573248 20
1794573253 20
1794573258 20
1794573263 20
1794573268 20
1794573273 20
1794573278 21
1794573283 21
1794573288 24
1794573293 24
1794573298 24
1794573303 24
1794573308 24
1794573313 24
1794573318 24
```
</details>

---

