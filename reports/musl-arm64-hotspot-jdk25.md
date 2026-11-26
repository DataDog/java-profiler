---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:16:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795691239 44
1795691244 44
1795691249 44
1795691254 44
1795691259 44
1795691264 44
1795691269 44
1795691274 44
1795691279 44
1795691284 44
1795691289 64
1795691294 64
1795691299 64
1795691304 64
1795691309 64
1795691314 64
1795691319 64
1795691324 64
1795691329 64
1795691334 64
```
</details>

---

