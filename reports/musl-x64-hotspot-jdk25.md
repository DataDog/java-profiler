---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 26.50/sec |
| Health Score | 1656% |
| Threads | 11 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 33.30/sec |
| Health Score | 2081% |
| Threads | 13 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (6 unique values: 58-90 cores)</summary>

```
1769697794 58
1769697799 62
1769697804 62
1769697809 62
1769697814 62
1769697819 62
1769697824 62
1769697829 62
1769697834 62
1769697839 62
1769697844 62
1769697849 66
1769697854 66
1769697859 66
1769697864 66
1769697869 66
1769697874 66
1769697879 63
1769697884 63
1769697889 63
```
</details>

---

