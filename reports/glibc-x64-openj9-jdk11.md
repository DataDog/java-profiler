---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 79-88 cores)</summary>

```
1794594676 82
1794594681 82
1794594686 82
1794594691 82
1794594696 79
1794594701 79
1794594706 79
1794594711 79
1794594716 79
1794594721 79
1794594726 79
1794594731 79
1794594736 79
1794594741 79
1794594746 79
1794594751 79
1794594756 79
1794594761 79
1794594766 88
1794594771 88
```
</details>

---

