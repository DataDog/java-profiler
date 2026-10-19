---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:04:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 11 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 9-24 cores)</summary>

```
1792400053 24
1792400058 24
1792400063 24
1792400069 24
1792400074 24
1792400079 17
1792400084 17
1792400089 10
1792400094 10
1792400099 10
1792400104 10
1792400109 9
1792400114 9
1792400119 9
1792400124 9
1792400129 9
1792400134 9
1792400139 9
1792400144 9
1792400149 9
```
</details>

---

