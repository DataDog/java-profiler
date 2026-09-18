---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:37:50 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1789716707 59
1789716712 59
1789716717 59
1789716722 59
1789716727 59
1789716732 59
1789716737 59
1789716742 59
1789716747 59
1789716752 59
1789716757 59
1789716762 59
1789716767 59
1789716772 61
1789716777 61
1789716782 61
1789716787 61
1789716792 61
1789716797 61
1789716802 61
```
</details>

---

