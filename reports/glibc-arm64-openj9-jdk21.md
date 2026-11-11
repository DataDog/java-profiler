---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:17:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 12 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 17 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 38-51 cores)</summary>

```
1794406364 51
1794406369 51
1794406374 51
1794406379 51
1794406384 51
1794406389 46
1794406394 46
1794406399 46
1794406404 46
1794406409 46
1794406414 46
1794406419 46
1794406424 46
1794406429 46
1794406434 46
1794406439 38
1794406444 38
1794406449 43
1794406454 43
1794406459 38
```
</details>

---

