---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:16:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 13 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794582677 48
1794582682 48
1794582687 48
1794582692 48
1794582697 48
1794582702 48
1794582707 48
1794582712 48
1794582717 48
1794582722 48
1794582727 48
1794582732 48
1794582737 48
1794582742 48
1794582747 48
1794582752 48
1794582757 48
1794582762 48
1794582767 48
1794582772 48
```
</details>

---

