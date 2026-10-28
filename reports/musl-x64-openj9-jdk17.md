---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 20:01:54 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (1 unique values: 8-8 cores)</summary>

```
1793145442 8
1793145447 8
1793145452 8
1793145457 8
1793145462 8
1793145467 8
1793145472 8
1793145477 8
1793145482 8
1793145487 8
1793145492 8
1793145497 8
1793145502 8
1793145507 8
1793145512 8
1793145517 8
1793145522 8
1793145527 8
1793145532 8
1793145537 8
```
</details>

---

