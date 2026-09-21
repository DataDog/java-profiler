---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 04:47:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 31-58 cores)</summary>

```
1789979941 48
1789979946 48
1789979951 48
1789979956 48
1789979961 48
1789979966 58
1789979971 58
1789979976 58
1789979981 58
1789979986 58
1789979991 58
1789979996 58
1789980001 41
1789980006 41
1789980011 41
1789980016 41
1789980021 41
1789980026 41
1789980031 41
1789980036 41
```
</details>

---

