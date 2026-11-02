---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 43 |
| Sample Rate | 0.72/sec |
| Health Score | 45% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 44-51 cores)</summary>

```
1793616699 46
1793616704 46
1793616709 51
1793616714 51
1793616719 51
1793616724 51
1793616729 51
1793616734 51
1793616740 51
1793616745 51
1793616750 47
1793616755 47
1793616760 47
1793616765 47
1793616770 47
1793616775 47
1793616780 44
1793616785 44
1793616790 44
1793616795 44
```
</details>

---

