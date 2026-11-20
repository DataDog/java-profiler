---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:40:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 64-73 cores)</summary>

```
1795192422 64
1795192427 64
1795192432 64
1795192437 64
1795192442 64
1795192447 64
1795192452 73
1795192457 73
1795192462 73
1795192467 73
1795192472 73
1795192477 73
1795192482 65
1795192487 65
1795192492 69
1795192497 69
1795192502 69
1795192507 69
1795192512 69
1795192517 69
```
</details>

---

