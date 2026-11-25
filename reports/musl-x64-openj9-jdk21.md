---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:19:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1795641281 82
1795641286 82
1795641291 82
1795641296 82
1795641301 82
1795641306 82
1795641311 82
1795641316 80
1795641321 80
1795641326 80
1795641331 80
1795641336 80
1795641341 80
1795641346 80
1795641351 80
1795641356 80
1795641361 80
1795641366 82
1795641371 82
1795641376 82
```
</details>

---

