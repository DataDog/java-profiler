---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-20 05:14:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795169259 50
1795169264 50
1795169269 50
1795169274 50
1795169279 50
1795169284 50
1795169289 50
1795169294 50
1795169299 50
1795169304 50
1795169309 50
1795169314 50
1795169319 50
1795169324 50
1795169329 50
1795169334 50
1795169339 50
1795169344 50
1795169349 50
1795169354 50
```
</details>

---

