---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:31:16 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 12 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795008390 51
1795008395 51
1795008400 64
1795008405 64
1795008410 64
1795008415 64
1795008420 64
1795008425 64
1795008430 64
1795008435 64
1795008440 64
1795008445 64
1795008450 64
1795008455 64
1795008460 64
1795008465 64
1795008470 64
1795008475 64
1795008480 64
1795008485 64
```
</details>

---

