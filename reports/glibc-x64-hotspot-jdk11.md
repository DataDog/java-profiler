---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 07:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 53-59 cores)</summary>

```
1777462535 58
1777462540 58
1777462545 58
1777462550 58
1777462555 58
1777462560 58
1777462565 58
1777462570 54
1777462575 54
1777462580 54
1777462585 54
1777462590 54
1777462595 54
1777462600 54
1777462605 54
1777462610 59
1777462615 59
1777462620 59
1777462625 59
1777462630 59
```
</details>

---

