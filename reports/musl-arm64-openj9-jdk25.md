---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-07 10:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 49-53 cores)</summary>

```
1791384054 53
1791384059 53
1791384064 53
1791384069 53
1791384074 53
1791384079 53
1791384084 53
1791384089 53
1791384094 53
1791384099 53
1791384104 53
1791384109 53
1791384114 53
1791384119 53
1791384124 53
1791384129 49
1791384134 49
1791384139 49
1791384144 49
1791384149 49
```
</details>

---

