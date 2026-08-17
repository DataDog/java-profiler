---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 01:02:28 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1041 |
| Sample Rate | 17.35/sec |
| Health Score | 1084% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1786942375 26
1786942380 26
1786942385 26
1786942390 26
1786942395 28
1786942400 28
1786942405 28
1786942410 28
1786942415 28
1786942420 28
1786942425 28
1786942430 28
1786942435 28
1786942440 28
1786942445 28
1786942450 28
1786942455 28
1786942460 28
1786942465 28
1786942470 28
```
</details>

---

