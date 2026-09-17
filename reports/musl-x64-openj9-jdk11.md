---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:54:17 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 52-96 cores)</summary>

```
1789667272 96
1789667277 96
1789667282 60
1789667287 60
1789667292 60
1789667297 60
1789667302 60
1789667307 60
1789667312 60
1789667317 60
1789667322 60
1789667327 60
1789667332 60
1789667337 60
1789667342 60
1789667347 60
1789667352 60
1789667357 60
1789667362 60
1789667367 60
```
</details>

---

