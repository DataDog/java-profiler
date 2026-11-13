---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:08:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 14 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794567788 46
1794567793 46
1794567798 46
1794567803 46
1794567808 46
1794567813 48
1794567818 48
1794567823 48
1794567828 48
1794567833 48
1794567838 48
1794567843 48
1794567848 48
1794567853 48
1794567858 48
1794567863 48
1794567868 48
1794567873 48
1794567878 48
1794567883 48
```
</details>

---

