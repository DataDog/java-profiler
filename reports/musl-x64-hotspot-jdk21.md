---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:22:28 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 10 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 12 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1770826259 91
1770826264 91
1770826269 91
1770826274 91
1770826279 91
1770826284 91
1770826289 91
1770826294 91
1770826299 91
1770826304 91
1770826309 91
1770826314 91
1770826319 91
1770826324 91
1770826329 91
1770826334 91
1770826339 91
1770826344 91
1770826349 91
1770826354 89
```
</details>

---

