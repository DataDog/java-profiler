---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:41:05 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789673452 38
1789673457 38
1789673462 38
1789673467 38
1789673472 38
1789673477 38
1789673482 38
1789673487 38
1789673492 38
1789673497 38
1789673502 38
1789673507 48
1789673512 48
1789673517 48
1789673522 48
1789673527 48
1789673532 48
1789673537 48
1789673542 48
1789673547 48
```
</details>

---

