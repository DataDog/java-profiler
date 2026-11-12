---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:57:02 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794509518 38
1794509523 38
1794509529 38
1794509534 38
1794509539 38
1794509544 38
1794509549 38
1794509554 38
1794509559 38
1794509564 43
1794509569 43
1794509574 43
1794509579 43
1794509584 43
1794509589 43
1794509594 43
1794509599 43
1794509604 43
1794509609 43
1794509614 43
```
</details>

---

