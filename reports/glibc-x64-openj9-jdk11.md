---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788475538 64
1788475543 64
1788475548 64
1788475553 64
1788475558 64
1788475563 64
1788475568 62
1788475573 62
1788475578 62
1788475583 62
1788475588 62
1788475593 62
1788475598 64
1788475603 64
1788475608 64
1788475613 64
1788475618 62
1788475623 62
1788475628 62
1788475633 62
```
</details>

---

