---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:48:37 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 15 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 28-33 cores)</summary>

```
1795027356 28
1795027361 28
1795027366 28
1795027371 28
1795027376 28
1795027381 28
1795027386 33
1795027391 33
1795027396 33
1795027401 33
1795027406 33
1795027411 33
1795027416 33
1795027421 33
1795027426 33
1795027431 33
1795027436 33
1795027441 33
1795027446 33
1795027451 33
```
</details>

---

