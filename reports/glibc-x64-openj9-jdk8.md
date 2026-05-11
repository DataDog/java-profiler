---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-11 10:05:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 70-83 cores)</summary>

```
1778508049 71
1778508054 71
1778508059 71
1778508064 71
1778508069 74
1778508074 74
1778508079 74
1778508084 70
1778508089 70
1778508094 70
1778508099 70
1778508104 70
1778508109 76
1778508114 76
1778508119 76
1778508124 83
1778508129 83
1778508134 83
1778508139 83
1778508144 83
```
</details>

---

