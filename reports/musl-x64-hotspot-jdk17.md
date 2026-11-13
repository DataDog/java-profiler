---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:44:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 64-88 cores)</summary>

```
1794584393 64
1794584398 64
1794584403 88
1794584408 88
1794584413 88
1794584418 88
1794584423 88
1794584428 88
1794584433 88
1794584438 88
1794584443 88
1794584448 88
1794584453 88
1794584458 88
1794584463 88
1794584468 71
1794584473 71
1794584478 71
1794584483 71
1794584488 71
```
</details>

---

