---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 19:11:33 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 31-48 cores)</summary>

```
1789686400 31
1789686405 31
1789686410 31
1789686415 31
1789686420 31
1789686425 31
1789686430 31
1789686435 31
1789686440 31
1789686445 31
1789686450 31
1789686455 31
1789686460 31
1789686465 31
1789686470 31
1789686475 31
1789686480 31
1789686485 48
1789686490 48
1789686495 48
```
</details>

---

