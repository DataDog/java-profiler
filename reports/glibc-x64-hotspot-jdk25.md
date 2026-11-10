---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 09:14:00 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
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
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 12 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (6 unique values: 67-94 cores)</summary>

```
1794319728 71
1794319733 71
1794319738 69
1794319743 69
1794319748 69
1794319753 69
1794319758 69
1794319763 69
1794319768 69
1794319773 67
1794319778 67
1794319783 69
1794319788 69
1794319793 73
1794319798 73
1794319803 73
1794319808 73
1794319813 73
1794319818 73
1794319823 73
```
</details>

---

