---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-11 01:02:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1791694716 21
1791694721 21
1791694726 21
1791694731 21
1791694736 21
1791694741 21
1791694746 21
1791694752 21
1791694757 21
1791694762 21
1791694767 21
1791694772 21
1791694777 21
1791694782 21
1791694787 19
1791694792 19
1791694797 19
1791694802 19
1791694807 19
1791694812 19
```
</details>

---

