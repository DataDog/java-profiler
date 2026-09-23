---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 16:03:20 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (4 unique values: 38-42 cores)</summary>

```
1790193517 42
1790193522 42
1790193527 42
1790193532 41
1790193537 41
1790193542 41
1790193547 41
1790193552 41
1790193557 41
1790193562 41
1790193567 41
1790193572 41
1790193577 41
1790193582 41
1790193587 41
1790193592 40
1790193597 40
1790193602 40
1790193607 38
1790193613 38
```
</details>

---

