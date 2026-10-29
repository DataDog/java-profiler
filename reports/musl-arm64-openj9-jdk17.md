---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 13:49:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 12 |
| Allocations | 96 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793295819 48
1793295824 48
1793295829 48
1793295834 48
1793295839 48
1793295844 48
1793295849 48
1793295854 48
1793295859 48
1793295865 48
1793295870 48
1793295875 48
1793295880 48
1793295885 48
1793295890 48
1793295895 48
1793295900 48
1793295905 48
1793295910 48
1793295915 48
```
</details>

---

