---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1788475529 29
1788475534 29
1788475539 29
1788475544 29
1788475549 29
1788475554 29
1788475559 24
1788475564 24
1788475569 24
1788475574 24
1788475579 24
1788475584 24
1788475589 24
1788475594 24
1788475599 29
1788475604 29
1788475609 29
1788475614 29
1788475619 29
1788475624 29
```
</details>

---

