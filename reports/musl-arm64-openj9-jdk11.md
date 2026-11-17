---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 13:29:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1010 |
| Sample Rate | 16.83/sec |
| Health Score | 1052% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 27-41 cores)</summary>

```
1794939897 41
1794939902 41
1794939907 41
1794939912 41
1794939917 41
1794939922 41
1794939927 41
1794939932 41
1794939937 41
1794939942 31
1794939947 31
1794939952 32
1794939957 32
1794939962 32
1794939967 27
1794939972 27
1794939977 27
1794939982 27
1794939987 27
1794939992 27
```
</details>

---

