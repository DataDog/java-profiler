---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 16:03:18 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 39-43 cores)</summary>

```
1790193535 42
1790193540 42
1790193545 42
1790193550 42
1790193555 42
1790193560 42
1790193565 43
1790193570 43
1790193575 43
1790193580 43
1790193585 43
1790193590 43
1790193595 43
1790193600 41
1790193605 41
1790193610 41
1790193615 41
1790193620 39
1790193625 39
1790193630 39
```
</details>

---

