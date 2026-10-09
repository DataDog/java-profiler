---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 10:23:30 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1791555523 48
1791555528 48
1791555533 53
1791555538 53
1791555543 53
1791555548 53
1791555553 53
1791555558 53
1791555563 53
1791555568 53
1791555573 53
1791555578 53
1791555583 53
1791555588 53
1791555593 53
1791555598 53
1791555603 53
1791555608 53
1791555613 53
1791555618 53
```
</details>

---

