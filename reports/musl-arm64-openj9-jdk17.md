---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 19:51:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 8 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793404049 29
1793404054 29
1793404059 29
1793404064 29
1793404069 29
1793404074 29
1793404079 29
1793404084 29
1793404089 29
1793404094 29
1793404099 29
1793404104 29
1793404109 29
1793404114 29
1793404119 29
1793404124 29
1793404129 29
1793404134 34
1793404139 34
1793404144 34
```
</details>

---

