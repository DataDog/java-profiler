---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 10:05:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1792591194 86
1792591199 86
1792591204 86
1792591209 88
1792591214 88
1792591219 88
1792591224 88
1792591229 88
1792591234 88
1792591239 88
1792591244 88
1792591249 90
1792591254 90
1792591259 90
1792591264 90
1792591269 90
1792591274 90
1792591279 90
1792591284 90
1792591289 90
```
</details>

---

