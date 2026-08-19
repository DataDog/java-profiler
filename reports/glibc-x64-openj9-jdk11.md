---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 06:56:25 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 80-96 cores)</summary>

```
1787136717 96
1787136722 96
1787136727 96
1787136732 96
1787136737 96
1787136742 96
1787136747 96
1787136752 96
1787136757 96
1787136762 96
1787136767 96
1787136772 96
1787136777 96
1787136782 96
1787136787 96
1787136792 96
1787136797 96
1787136802 96
1787136807 96
1787136812 96
```
</details>

---

