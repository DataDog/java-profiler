---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:28:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 39-41 cores)</summary>

```
1791530607 41
1791530612 41
1791530617 41
1791530622 41
1791530627 41
1791530632 41
1791530637 41
1791530642 41
1791530647 41
1791530652 41
1791530657 41
1791530662 39
1791530667 39
1791530672 39
1791530677 39
1791530682 39
1791530687 41
1791530692 41
1791530697 41
1791530702 41
```
</details>

---

