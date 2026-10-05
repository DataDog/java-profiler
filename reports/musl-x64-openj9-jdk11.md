---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 13:24:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 67-84 cores)</summary>

```
1791220764 79
1791220769 79
1791220774 79
1791220779 79
1791220784 67
1791220789 67
1791220794 67
1791220799 67
1791220804 67
1791220809 67
1791220814 67
1791220819 67
1791220824 67
1791220829 67
1791220834 67
1791220839 84
1791220844 84
1791220849 84
1791220854 84
1791220859 84
```
</details>

---

