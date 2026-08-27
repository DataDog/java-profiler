---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787806382 64
1787806387 64
1787806392 64
1787806397 64
1787806402 64
1787806407 64
1787806412 64
1787806417 64
1787806422 64
1787806427 64
1787806432 64
1787806437 64
1787806442 64
1787806447 64
1787806452 64
1787806457 64
1787806462 64
1787806467 64
1787806472 64
1787806477 64
```
</details>

---

