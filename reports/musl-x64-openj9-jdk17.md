---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:49:03 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1789731839 72
1789731844 72
1789731849 72
1789731854 72
1789731859 72
1789731864 70
1789731869 70
1789731875 70
1789731880 72
1789731885 72
1789731890 72
1789731895 72
1789731900 72
1789731905 72
1789731910 74
1789731915 74
1789731920 76
1789731925 76
1789731930 76
1789731935 76
```
</details>

---

