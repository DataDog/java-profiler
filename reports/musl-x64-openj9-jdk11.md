---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793722731 62
1793722736 62
1793722741 62
1793722746 62
1793722751 62
1793722756 64
1793722761 64
1793722766 62
1793722771 62
1793722776 62
1793722781 62
1793722786 62
1793722791 62
1793722796 62
1793722801 62
1793722806 62
1793722811 62
1793722816 62
1793722821 62
1793722826 62
```
</details>

---

