---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 01:03:09 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1786337950 32
1786337955 32
1786337960 32
1786337965 32
1786337970 32
1786337975 29
1786337980 29
1786337985 29
1786337990 29
1786337995 29
1786338000 29
1786338005 29
1786338010 29
1786338015 29
1786338020 29
1786338025 29
1786338030 29
1786338035 29
1786338040 29
1786338045 29
```
</details>

---

