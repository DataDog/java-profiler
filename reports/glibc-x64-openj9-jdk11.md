---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 05:15:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 19-27 cores)</summary>

```
1777280999 19
1777281004 19
1777281009 19
1777281014 19
1777281019 19
1777281024 24
1777281029 24
1777281034 24
1777281039 24
1777281044 24
1777281049 24
1777281054 24
1777281059 24
1777281064 24
1777281069 24
1777281074 27
1777281079 27
1777281084 27
1777281089 27
1777281094 27
```
</details>

---

