---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-17 10:37:09 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 11 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 38-38 cores)</summary>

```
1794929295 38
1794929300 38
1794929305 38
1794929310 38
1794929315 38
1794929320 38
1794929325 38
1794929330 38
1794929335 38
1794929340 38
1794929345 38
1794929350 38
1794929355 38
1794929360 38
1794929365 38
1794929370 38
1794929375 38
1794929380 38
1794929385 38
1794929390 38
```
</details>

---

