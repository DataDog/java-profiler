---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 07:57:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793274799 30
1793274804 30
1793274809 30
1793274814 30
1793274819 30
1793274824 30
1793274829 30
1793274834 30
1793274839 30
1793274844 30
1793274849 30
1793274854 30
1793274859 30
1793274864 30
1793274869 30
1793274874 30
1793274879 30
1793274884 30
1793274889 30
1793274894 30
```
</details>

---

