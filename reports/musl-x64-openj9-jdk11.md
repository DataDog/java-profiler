---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 12:24:01 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
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
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1786119557 47
1786119562 47
1786119567 47
1786119572 47
1786119577 45
1786119582 45
1786119587 45
1786119592 45
1786119597 45
1786119602 45
1786119607 45
1786119612 45
1786119617 45
1786119622 45
1786119628 45
1786119633 45
1786119638 45
1786119643 45
1786119648 45
1786119653 45
```
</details>

---

