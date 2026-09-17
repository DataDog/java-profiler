---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:41:06 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1789673452 56
1789673457 56
1789673462 56
1789673467 56
1789673472 56
1789673477 58
1789673482 58
1789673487 58
1789673492 58
1789673497 58
1789673502 58
1789673507 58
1789673512 58
1789673517 58
1789673522 58
1789673527 58
1789673532 58
1789673537 58
1789673542 58
1789673547 58
```
</details>

---

