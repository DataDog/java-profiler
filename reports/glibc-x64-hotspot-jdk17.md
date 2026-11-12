---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 09:18:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 60-83 cores)</summary>

```
1794492686 72
1794492691 72
1794492696 72
1794492701 72
1794492706 72
1794492711 72
1794492716 72
1794492721 72
1794492726 72
1794492731 72
1794492736 72
1794492741 72
1794492746 70
1794492751 70
1794492756 70
1794492761 70
1794492766 70
1794492771 83
1794492776 83
1794492781 65
```
</details>

---

