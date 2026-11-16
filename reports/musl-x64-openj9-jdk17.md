---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:37:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 76-88 cores)</summary>

```
1794832290 86
1794832295 86
1794832300 86
1794832305 86
1794832310 86
1794832315 86
1794832320 86
1794832325 86
1794832330 86
1794832335 86
1794832340 86
1794832345 84
1794832350 84
1794832355 84
1794832360 84
1794832365 88
1794832370 88
1794832375 88
1794832380 76
1794832385 76
```
</details>

---

