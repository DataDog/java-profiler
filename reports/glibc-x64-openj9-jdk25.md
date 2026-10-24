---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-24 04:44:31 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 44-79 cores)</summary>

```
1792831121 79
1792831126 79
1792831131 79
1792831136 79
1792831141 79
1792831146 79
1792831151 79
1792831156 79
1792831161 79
1792831166 79
1792831171 79
1792831176 46
1792831181 46
1792831186 46
1792831191 46
1792831196 46
1792831201 46
1792831206 46
1792831211 46
1792831216 46
```
</details>

---

