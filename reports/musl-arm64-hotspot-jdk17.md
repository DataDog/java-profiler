---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:28:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795015393 33
1795015398 33
1795015403 33
1795015408 33
1795015413 33
1795015418 33
1795015423 33
1795015428 38
1795015433 38
1795015438 38
1795015443 38
1795015448 38
1795015453 38
1795015458 38
1795015463 38
1795015468 38
1795015473 38
1795015478 38
1795015483 38
1795015488 38
```
</details>

---

