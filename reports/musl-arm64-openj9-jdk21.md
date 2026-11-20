---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:56:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 45-59 cores)</summary>

```
1795171817 50
1795171822 50
1795171827 50
1795171832 50
1795171837 50
1795171842 50
1795171847 50
1795171852 50
1795171857 50
1795171862 50
1795171867 50
1795171872 50
1795171877 50
1795171882 50
1795171887 50
1795171892 50
1795171897 45
1795171902 45
1795171907 59
1795171912 59
```
</details>

---

