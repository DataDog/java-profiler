---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-24 15:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1787600230 82
1787600235 82
1787600240 82
1787600245 82
1787600250 82
1787600255 84
1787600260 84
1787600265 82
1787600270 82
1787600275 82
1787600280 82
1787600285 82
1787600290 82
1787600295 82
1787600300 84
1787600305 84
1787600310 84
1787600315 84
1787600320 84
1787600325 84
```
</details>

---

