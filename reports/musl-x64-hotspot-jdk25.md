---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 09:51:43 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1793630761 30
1793630766 30
1793630771 30
1793630776 30
1793630781 26
1793630786 26
1793630791 26
1793630796 26
1793630801 26
1793630806 26
1793630811 26
1793630816 26
1793630821 26
1793630826 26
1793630831 26
1793630836 26
1793630841 26
1793630846 26
1793630851 26
1793630856 26
```
</details>

---

