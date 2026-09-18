---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:37:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
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
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 917 |
| Sample Rate | 15.28/sec |
| Health Score | 955% |
| Threads | 10 |
| Allocations | 450 |

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

