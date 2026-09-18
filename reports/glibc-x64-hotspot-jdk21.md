---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 12:41:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1789749371 63
1789749376 63
1789749381 63
1789749386 63
1789749391 63
1789749396 63
1789749401 63
1789749406 65
1789749411 65
1789749416 65
1789749421 65
1789749426 65
1789749431 65
1789749436 65
1789749441 65
1789749446 65
1789749451 65
1789749456 65
1789749461 65
1789749466 65
```
</details>

---

