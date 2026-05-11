---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 18:32:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778538442 64
1778538447 64
1778538452 64
1778538457 64
1778538462 64
1778538467 59
1778538472 59
1778538477 59
1778538482 59
1778538487 59
1778538492 59
1778538497 59
1778538502 59
1778538507 59
1778538512 59
1778538517 59
1778538522 59
1778538527 59
1778538532 59
1778538537 59
```
</details>

---

