---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 09:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 80-90 cores)</summary>

```
1794492706 80
1794492711 88
1794492716 88
1794492721 88
1794492726 86
1794492731 86
1794492736 86
1794492741 86
1794492746 88
1794492751 88
1794492756 90
1794492761 90
1794492766 90
1794492771 90
1794492776 90
1794492781 90
1794492786 90
1794492791 90
1794492796 90
1794492801 90
```
</details>

---

