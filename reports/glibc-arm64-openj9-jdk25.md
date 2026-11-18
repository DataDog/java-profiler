---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:07:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 33-46 cores)</summary>

```
1795014230 44
1795014235 44
1795014240 44
1795014245 46
1795014250 46
1795014255 33
1795014260 33
1795014265 33
1795014270 33
1795014275 33
1795014280 33
1795014285 33
1795014290 33
1795014295 33
1795014300 33
1795014305 33
1795014310 33
1795014315 33
1795014320 33
1795014325 33
```
</details>

---

