---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:59:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 13-33 cores)</summary>

```
1795431402 13
1795431407 13
1795431412 13
1795431417 13
1795431422 13
1795431427 13
1795431432 13
1795431437 13
1795431442 33
1795431447 33
1795431452 33
1795431457 33
1795431462 33
1795431467 33
1795431472 33
1795431477 33
1795431482 33
1795431487 33
1795431492 33
1795431497 33
```
</details>

---

