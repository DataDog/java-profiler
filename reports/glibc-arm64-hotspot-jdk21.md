---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 20:59:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 13 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1793148939 28
1793148944 28
1793148949 28
1793148954 28
1793148959 28
1793148964 28
1793148969 28
1793148974 28
1793148979 28
1793148984 28
1793148989 28
1793148994 28
1793149000 28
1793149005 28
1793149010 28
1793149015 28
1793149020 28
1793149025 28
1793149030 28
1793149035 28
```
</details>

---

