---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 13:04:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 9 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787158832 46
1787158837 46
1787158842 46
1787158847 46
1787158852 46
1787158857 46
1787158862 46
1787158867 48
1787158872 48
1787158877 48
1787158882 48
1787158887 48
1787158892 48
1787158897 48
1787158902 48
1787158907 48
1787158912 48
1787158917 43
1787158922 43
1787158927 43
```
</details>

---

