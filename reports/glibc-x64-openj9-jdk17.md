---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-12 10:34:45 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 409 |

<details>
<summary>CPU Timeline (5 unique values: 70-77 cores)</summary>

```
1773325732 74
1773325737 74
1773325742 74
1773325747 74
1773325752 74
1773325757 74
1773325762 75
1773325767 75
1773325772 75
1773325777 77
1773325782 77
1773325787 77
1773325792 77
1773325797 77
1773325802 77
1773325807 77
1773325812 77
1773325817 70
1773325822 70
1773325827 70
```
</details>

---

