---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-04 09:37:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1788528772 66
1788528777 66
1788528782 66
1788528787 64
1788528792 64
1788528797 64
1788528802 64
1788528807 64
1788528812 64
1788528817 64
1788528822 64
1788528827 64
1788528832 64
1788528837 64
1788528842 66
1788528847 66
1788528852 66
1788528857 66
1788528862 66
1788528867 66
```
</details>

---

