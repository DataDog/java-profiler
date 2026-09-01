---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 01:00:01 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 11 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788238510 48
1788238515 48
1788238520 48
1788238525 48
1788238530 48
1788238535 48
1788238540 48
1788238545 48
1788238550 48
1788238555 48
1788238560 48
1788238565 48
1788238570 48
1788238575 43
1788238580 43
1788238585 43
1788238590 43
1788238595 43
1788238600 43
1788238605 43
```
</details>

---

