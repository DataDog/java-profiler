---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 964 |
| Sample Rate | 16.07/sec |
| Health Score | 1004% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 76-82 cores)</summary>

```
1794999763 76
1794999768 76
1794999773 76
1794999778 76
1794999783 76
1794999789 76
1794999794 76
1794999799 76
1794999804 76
1794999809 76
1794999814 76
1794999819 76
1794999824 76
1794999829 76
1794999834 76
1794999839 79
1794999844 79
1794999849 79
1794999854 76
1794999859 76
```
</details>

---

