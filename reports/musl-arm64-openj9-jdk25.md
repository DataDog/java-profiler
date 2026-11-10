---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:48:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 13 |
| Allocations | 170 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794325396 46
1794325401 46
1794325406 46
1794325411 46
1794325416 46
1794325421 46
1794325426 46
1794325431 46
1794325436 46
1794325441 41
1794325446 41
1794325451 41
1794325456 41
1794325461 41
1794325466 41
1794325471 41
1794325476 41
1794325481 41
1794325486 41
1794325491 41
```
</details>

---

