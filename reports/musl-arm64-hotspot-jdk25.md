---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:23:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 10 |
| Allocations | 124 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (5 unique values: 20-35 cores)</summary>

```
1793373475 25
1793373480 25
1793373485 25
1793373490 25
1793373495 20
1793373500 20
1793373505 20
1793373510 20
1793373515 25
1793373520 25
1793373525 30
1793373530 30
1793373535 30
1793373540 30
1793373545 35
1793373550 35
1793373555 26
1793373560 26
1793373565 26
1793373570 26
```
</details>

---

