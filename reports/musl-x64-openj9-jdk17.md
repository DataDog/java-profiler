---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 10:58:57 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 66-84 cores)</summary>

```
1787151285 84
1787151290 84
1787151295 84
1787151300 84
1787151305 84
1787151310 84
1787151315 84
1787151321 84
1787151326 84
1787151331 84
1787151336 68
1787151341 68
1787151346 68
1787151351 68
1787151356 66
1787151361 66
1787151366 66
1787151371 66
1787151376 66
1787151381 66
```
</details>

---

