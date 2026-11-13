---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:27:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1794572465 65
1794572470 65
1794572475 65
1794572480 65
1794572485 65
1794572490 65
1794572495 65
1794572500 65
1794572505 65
1794572510 65
1794572515 67
1794572520 67
1794572525 67
1794572531 67
1794572536 67
1794572541 67
1794572546 67
1794572551 67
1794572556 67
1794572561 67
```
</details>

---

