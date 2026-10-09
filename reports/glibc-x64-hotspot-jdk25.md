---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1791543764 32
1791543769 32
1791543774 32
1791543779 32
1791543784 32
1791543789 32
1791543794 32
1791543799 32
1791543804 32
1791543809 32
1791543814 32
1791543819 32
1791543824 32
1791543829 32
1791543834 28
1791543839 28
1791543844 28
1791543849 28
1791543854 28
1791543859 28
```
</details>

---

