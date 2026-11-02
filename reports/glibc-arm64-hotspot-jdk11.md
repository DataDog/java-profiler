---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:56:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 13 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793616764 34
1793616769 34
1793616774 34
1793616779 34
1793616784 34
1793616789 34
1793616794 34
1793616799 34
1793616804 34
1793616809 34
1793616814 34
1793616819 34
1793616824 34
1793616829 34
1793616834 34
1793616839 34
1793616844 34
1793616849 34
1793616854 34
1793616859 34
```
</details>

---

