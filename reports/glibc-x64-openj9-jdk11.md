---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:49:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 37-46 cores)</summary>

```
1777477244 46
1777477249 46
1777477254 46
1777477259 42
1777477264 42
1777477269 42
1777477274 42
1777477279 42
1777477284 37
1777477289 37
1777477294 37
1777477299 37
1777477304 37
1777477309 37
1777477314 37
1777477319 37
1777477324 37
1777477329 37
1777477334 37
1777477339 37
```
</details>

---

