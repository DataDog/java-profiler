---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 08:32:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795181321 50
1795181326 64
1795181331 64
1795181336 50
1795181341 50
1795181346 50
1795181351 50
1795181356 50
1795181361 50
1795181366 50
1795181371 50
1795181376 50
1795181381 50
1795181386 50
1795181391 50
1795181396 50
1795181401 50
1795181407 50
1795181412 50
1795181417 50
```
</details>

---

