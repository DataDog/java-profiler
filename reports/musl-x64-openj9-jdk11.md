---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:08:26 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 59-68 cores)</summary>

```
1789995743 59
1789995748 59
1789995753 59
1789995758 59
1789995763 59
1789995768 61
1789995773 61
1789995778 63
1789995783 63
1789995788 68
1789995793 68
1789995798 68
1789995803 68
1789995808 68
1789995813 68
1789995818 68
1789995823 68
1789995828 68
1789995833 68
1789995838 68
```
</details>

---

