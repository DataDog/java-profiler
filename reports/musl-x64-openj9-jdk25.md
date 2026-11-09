---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 18:56:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794268260 49
1794268265 49
1794268270 49
1794268275 49
1794268280 49
1794268285 51
1794268290 51
1794268295 51
1794268300 51
1794268305 51
1794268310 51
1794268315 51
1794268320 51
1794268325 51
1794268330 51
1794268335 51
1794268340 51
1794268345 51
1794268350 51
1794268355 51
```
</details>

---

