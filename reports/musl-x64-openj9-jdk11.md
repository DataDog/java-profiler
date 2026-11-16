---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:37:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 9 |
| Allocations | 576 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1794832290 67
1794832295 67
1794832300 67
1794832305 67
1794832310 67
1794832315 67
1794832320 67
1794832325 67
1794832330 67
1794832335 67
1794832340 67
1794832345 67
1794832350 67
1794832355 67
1794832360 67
1794832365 67
1794832370 71
1794832375 71
1794832380 69
1794832385 69
```
</details>

---

