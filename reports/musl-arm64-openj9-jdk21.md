---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 05:04:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 190 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 20-27 cores)</summary>

```
1792400064 27
1792400069 27
1792400074 27
1792400079 27
1792400084 27
1792400089 27
1792400094 27
1792400099 27
1792400104 27
1792400109 27
1792400114 27
1792400119 27
1792400124 23
1792400129 23
1792400134 23
1792400139 23
1792400144 23
1792400149 23
1792400154 23
1792400159 23
```
</details>

---

