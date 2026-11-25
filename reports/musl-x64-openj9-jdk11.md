---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:21:58 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 38-57 cores)</summary>

```
1795641271 57
1795641276 57
1795641281 57
1795641286 55
1795641291 55
1795641296 55
1795641301 55
1795641306 55
1795641311 57
1795641316 57
1795641321 38
1795641326 38
1795641331 38
1795641336 38
1795641341 38
1795641346 38
1795641351 38
1795641356 38
1795641361 38
1795641366 38
```
</details>

---

