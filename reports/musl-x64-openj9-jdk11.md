---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:10:05 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 17-29 cores)</summary>

```
1777392247 29
1777392252 29
1777392257 27
1777392262 27
1777392267 27
1777392272 27
1777392277 27
1777392282 27
1777392287 27
1777392292 27
1777392297 27
1777392302 27
1777392307 27
1777392312 27
1777392317 27
1777392322 27
1777392327 22
1777392332 22
1777392337 22
1777392342 22
```
</details>

---

