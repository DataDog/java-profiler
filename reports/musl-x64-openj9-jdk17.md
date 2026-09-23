---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 16:03:20 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1790193507 57
1790193512 57
1790193517 57
1790193522 57
1790193527 57
1790193532 57
1790193537 57
1790193542 55
1790193547 55
1790193552 55
1790193557 55
1790193562 55
1790193567 55
1790193572 55
1790193577 57
1790193582 57
1790193587 57
1790193592 57
1790193597 57
1790193602 57
```
</details>

---

