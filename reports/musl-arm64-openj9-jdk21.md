---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 10:39:00 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 36-45 cores)</summary>

```
1789741915 45
1789741920 41
1789741925 41
1789741930 41
1789741935 41
1789741940 41
1789741945 41
1789741950 41
1789741955 41
1789741960 36
1789741965 36
1789741970 37
1789741975 37
1789741980 37
1789741985 37
1789741990 37
1789741995 37
1789742000 37
1789742005 37
1789742010 37
```
</details>

---

