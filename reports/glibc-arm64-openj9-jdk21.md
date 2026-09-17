---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 06:26:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (5 unique values: 11-48 cores)</summary>

```
1789640514 43
1789640519 43
1789640524 43
1789640529 48
1789640534 48
1789640539 48
1789640544 48
1789640549 48
1789640554 48
1789640559 48
1789640564 48
1789640569 48
1789640574 48
1789640579 48
1789640584 39
1789640589 39
1789640594 39
1789640599 39
1789640604 34
1789640609 34
```
</details>

---

