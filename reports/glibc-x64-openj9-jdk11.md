---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 09:42:12 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 48-55 cores)</summary>

```
1792762730 48
1792762735 48
1792762740 48
1792762745 48
1792762750 48
1792762755 48
1792762760 48
1792762765 48
1792762770 48
1792762775 48
1792762780 53
1792762785 53
1792762790 53
1792762795 53
1792762800 55
1792762805 55
1792762810 55
1792762815 55
1792762820 55
1792762825 55
```
</details>

---

