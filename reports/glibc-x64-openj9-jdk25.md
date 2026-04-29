---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:49:27 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 61-66 cores)</summary>

```
1777477243 66
1777477248 66
1777477253 66
1777477259 66
1777477264 66
1777477269 66
1777477274 66
1777477279 61
1777477284 61
1777477289 61
1777477294 61
1777477299 64
1777477304 64
1777477309 64
1777477314 64
1777477319 64
1777477324 64
1777477329 64
1777477334 64
1777477339 64
```
</details>

---

