---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-29 07:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 53-74 cores)</summary>

```
1777462520 71
1777462525 71
1777462530 71
1777462535 71
1777462540 71
1777462545 71
1777462550 66
1777462555 66
1777462560 74
1777462565 74
1777462570 74
1777462575 54
1777462580 54
1777462585 53
1777462590 53
1777462595 53
1777462600 53
1777462605 57
1777462610 57
1777462615 57
```
</details>

---

