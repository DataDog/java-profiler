---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 10:36:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1793370682 12
1793370687 12
1793370692 10
1793370697 10
1793370702 10
1793370707 10
1793370712 10
1793370717 10
1793370722 12
1793370727 12
1793370732 12
1793370737 12
1793370742 12
1793370747 12
1793370752 12
1793370757 12
1793370762 32
1793370767 32
1793370772 32
1793370777 32
```
</details>

---

