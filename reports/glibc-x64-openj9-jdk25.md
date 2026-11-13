---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 13:06:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 10 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 63-69 cores)</summary>

```
1794592837 67
1794592842 67
1794592847 67
1794592852 67
1794592857 67
1794592862 67
1794592867 67
1794592872 67
1794592877 67
1794592882 67
1794592887 65
1794592892 65
1794592897 65
1794592902 65
1794592907 67
1794592912 67
1794592917 67
1794592922 63
1794592927 63
1794592932 63
```
</details>

---

