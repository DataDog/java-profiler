---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:47:04 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 10 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1789979941 43
1789979946 43
1789979951 43
1789979956 43
1789979961 41
1789979966 41
1789979971 41
1789979976 41
1789979981 41
1789979986 41
1789979991 41
1789979996 41
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

