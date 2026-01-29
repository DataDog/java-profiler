---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:43:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 22.90/sec |
| Health Score | 1431% |
| Threads | 11 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 31.60/sec |
| Health Score | 1975% |
| Threads | 12 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 84-96 cores)</summary>

```
1769708252 84
1769708257 84
1769708262 84
1769708267 84
1769708272 84
1769708277 84
1769708282 84
1769708287 84
1769708292 84
1769708297 84
1769708302 84
1769708307 84
1769708312 84
1769708317 84
1769708322 84
1769708327 84
1769708332 96
1769708337 96
1769708342 96
1769708347 96
```
</details>

---

