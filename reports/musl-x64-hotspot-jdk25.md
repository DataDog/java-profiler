---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:16:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 54-86 cores)</summary>

```
1794582658 54
1794582663 54
1794582668 71
1794582673 71
1794582678 71
1794582683 71
1794582688 71
1794582693 71
1794582698 67
1794582703 67
1794582708 67
1794582713 67
1794582718 67
1794582723 67
1794582728 67
1794582733 67
1794582738 67
1794582743 67
1794582748 67
1794582753 67
```
</details>

---

