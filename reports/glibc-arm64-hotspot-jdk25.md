---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 09:29:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1792761944 46
1792761949 46
1792761954 46
1792761959 46
1792761964 46
1792761969 46
1792761974 46
1792761979 46
1792761984 46
1792761989 46
1792761994 41
1792761999 41
1792762004 41
1792762009 41
1792762014 41
1792762019 41
1792762024 43
1792762029 43
1792762034 43
1792762039 43
```
</details>

---

