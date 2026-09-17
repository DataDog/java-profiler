---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:35:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 26-64 cores)</summary>

```
1789673417 64
1789673422 64
1789673427 31
1789673432 31
1789673437 31
1789673442 31
1789673447 31
1789673452 31
1789673457 31
1789673462 31
1789673467 31
1789673472 31
1789673477 31
1789673482 31
1789673487 31
1789673492 31
1789673497 31
1789673502 31
1789673507 31
1789673512 31
```
</details>

---

