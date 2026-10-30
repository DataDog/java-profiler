---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 11:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 71-79 cores)</summary>

```
1793374888 71
1793374893 71
1793374898 71
1793374903 71
1793374908 74
1793374913 74
1793374918 74
1793374923 79
1793374928 79
1793374933 79
1793374938 79
1793374943 76
1793374948 76
1793374953 76
1793374958 76
1793374963 76
1793374968 76
1793374973 76
1793374978 74
1793374983 74
```
</details>

---

