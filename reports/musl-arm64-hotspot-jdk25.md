---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:48:11 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794325381 41
1794325386 46
1794325391 46
1794325396 46
1794325401 46
1794325406 46
1794325411 46
1794325416 46
1794325421 46
1794325426 46
1794325431 46
1794325436 46
1794325441 46
1794325446 46
1794325451 46
1794325456 46
1794325461 46
1794325466 46
1794325471 46
1794325476 46
```
</details>

---

