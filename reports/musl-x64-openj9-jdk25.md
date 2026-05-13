---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-13 11:08:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 67-90 cores)</summary>

```
1778684646 80
1778684651 80
1778684656 80
1778684661 80
1778684666 80
1778684671 80
1778684676 80
1778684681 80
1778684686 80
1778684691 80
1778684696 80
1778684701 80
1778684706 80
1778684711 80
1778684716 80
1778684721 85
1778684726 85
1778684731 85
1778684736 90
1778684741 90
```
</details>

---

