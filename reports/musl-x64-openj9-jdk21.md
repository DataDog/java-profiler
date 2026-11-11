---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 13:18:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (5 unique values: 80-92 cores)</summary>

```
1794420798 90
1794420803 90
1794420808 92
1794420813 92
1794420818 92
1794420823 83
1794420828 83
1794420833 80
1794420838 80
1794420843 80
1794420848 82
1794420853 82
1794420858 82
1794420863 82
1794420868 82
1794420873 82
1794420878 82
1794420883 82
1794420888 82
1794420893 82
```
</details>

---

