---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:38:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1795001569 60
1795001574 60
1795001579 60
1795001584 60
1795001589 60
1795001594 60
1795001599 60
1795001604 60
1795001609 60
1795001614 60
1795001619 60
1795001624 60
1795001629 60
1795001634 60
1795001639 60
1795001644 62
1795001649 62
1795001654 62
1795001659 62
1795001664 62
```
</details>

---

