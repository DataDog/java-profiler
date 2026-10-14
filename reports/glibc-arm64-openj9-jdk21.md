---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 10:47:47 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1791989008 42
1791989013 42
1791989018 42
1791989023 42
1791989028 42
1791989033 42
1791989038 42
1791989043 42
1791989048 42
1791989053 42
1791989058 47
1791989063 47
1791989068 47
1791989073 47
1791989078 47
1791989083 47
1791989088 47
1791989093 47
1791989098 47
1791989103 47
```
</details>

---

