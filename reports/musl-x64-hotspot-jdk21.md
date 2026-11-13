---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:01:31 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1794585409 90
1794585414 90
1794585419 90
1794585424 90
1794585429 90
1794585434 90
1794585439 88
1794585444 88
1794585449 88
1794585454 88
1794585459 88
1794585464 88
1794585469 88
1794585474 88
1794585479 88
1794585484 88
1794585489 88
1794585494 88
1794585499 88
1794585504 88
```
</details>

---

