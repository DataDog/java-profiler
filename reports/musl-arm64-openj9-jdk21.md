---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:28:31 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 12 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795630964 64
1795630969 64
1795630974 64
1795630979 64
1795630984 64
1795630989 64
1795630994 64
1795630999 64
1795631004 64
1795631009 64
1795631014 64
1795631019 64
1795631024 64
1795631029 64
1795631034 64
1795631039 64
1795631044 64
1795631049 64
1795631054 64
1795631059 64
```
</details>

---

