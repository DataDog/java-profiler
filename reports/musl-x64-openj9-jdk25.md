---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-31 11:44:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 12 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 84-96 cores)</summary>

```
1788190764 96
1788190769 96
1788190774 96
1788190779 96
1788190784 96
1788190789 96
1788190794 96
1788190799 92
1788190804 92
1788190809 92
1788190814 92
1788190819 92
1788190824 92
1788190829 92
1788190834 92
1788190839 92
1788190844 92
1788190849 92
1788190854 92
1788190859 92
```
</details>

---

