---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-02 00:58:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1003 |
| Sample Rate | 16.72/sec |
| Health Score | 1045% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 74-91 cores)</summary>

```
1790916820 79
1790916826 79
1790916831 79
1790916836 79
1790916841 79
1790916846 79
1790916851 79
1790916856 79
1790916861 79
1790916866 79
1790916871 79
1790916876 79
1790916881 74
1790916886 74
1790916891 74
1790916896 74
1790916901 74
1790916906 74
1790916911 74
1790916916 74
```
</details>

---

