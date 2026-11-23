---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:49:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 53-74 cores)</summary>

```
1795430717 74
1795430722 74
1795430727 74
1795430732 74
1795430737 74
1795430742 74
1795430747 74
1795430752 74
1795430757 74
1795430762 74
1795430767 57
1795430772 57
1795430777 57
1795430782 57
1795430787 57
1795430792 57
1795430797 57
1795430802 57
1795430807 57
1795430812 57
```
</details>

---

