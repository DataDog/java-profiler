---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 08:29:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 938 |
| Sample Rate | 15.63/sec |
| Health Score | 977% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 33-53 cores)</summary>

```
1791289502 53
1791289507 53
1791289512 53
1791289517 53
1791289522 53
1791289527 53
1791289532 53
1791289537 53
1791289542 53
1791289547 53
1791289552 53
1791289557 53
1791289562 53
1791289567 53
1791289572 53
1791289577 53
1791289583 53
1791289588 33
1791289593 33
1791289598 33
```
</details>

---

