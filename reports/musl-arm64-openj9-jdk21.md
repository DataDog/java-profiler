---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:50:16 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 13 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (4 unique values: 40-44 cores)</summary>

```
1789738872 40
1789738877 42
1789738882 42
1789738887 42
1789738892 42
1789738897 44
1789738902 44
1789738907 44
1789738912 44
1789738917 44
1789738922 44
1789738927 44
1789738932 44
1789738937 44
1789738942 44
1789738947 44
1789738952 42
1789738957 42
1789738962 41
1789738967 41
```
</details>

---

