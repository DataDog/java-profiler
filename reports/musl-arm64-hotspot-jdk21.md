---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 09:26:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 7 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1787318479 34
1787318484 34
1787318489 34
1787318495 34
1787318500 34
1787318505 34
1787318510 34
1787318515 36
1787318520 36
1787318525 36
1787318530 36
1787318535 36
1787318540 36
1787318545 36
1787318550 36
1787318555 36
1787318560 36
1787318565 36
1787318570 36
1787318575 36
```
</details>

---

