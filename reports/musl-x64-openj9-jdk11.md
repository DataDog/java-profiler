---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:02:16 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 93 |
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
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 71-93 cores)</summary>

```
1794427036 71
1794427041 71
1794427046 71
1794427051 71
1794427056 71
1794427061 71
1794427066 71
1794427071 71
1794427076 71
1794427081 71
1794427086 71
1794427091 93
1794427096 93
1794427101 93
1794427106 93
1794427111 93
1794427116 93
1794427121 93
1794427126 93
1794427131 93
```
</details>

---

