---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:36:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 6-15 cores)</summary>

```
1794594686 6
1794594691 6
1794594696 6
1794594701 6
1794594706 6
1794594711 6
1794594716 6
1794594721 6
1794594726 6
1794594731 6
1794594736 6
1794594741 6
1794594746 6
1794594751 15
1794594756 15
1794594761 15
1794594766 15
1794594771 15
1794594776 15
1794594781 15
```
</details>

---

