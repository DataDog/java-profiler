---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-09 07:06:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1791543754 40
1791543759 40
1791543764 40
1791543769 40
1791543774 40
1791543779 40
1791543784 40
1791543789 40
1791543794 40
1791543799 40
1791543804 40
1791543809 40
1791543814 40
1791543819 40
1791543824 40
1791543829 40
1791543834 40
1791543839 40
1791543844 40
1791543849 35
```
</details>

---

