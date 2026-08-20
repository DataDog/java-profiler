---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:32:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 887 |
| Sample Rate | 14.78/sec |
| Health Score | 924% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1787232421 81
1787232426 81
1787232431 81
1787232436 81
1787232441 81
1787232446 81
1787232451 81
1787232456 81
1787232461 81
1787232466 73
1787232471 73
1787232476 73
1787232481 73
1787232486 73
1787232491 73
1787232496 73
1787232501 73
1787232506 73
1787232511 73
1787232516 73
```
</details>

---

