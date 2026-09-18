---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:34:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 10 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 27-64 cores)</summary>

```
1789719945 27
1789719950 27
1789719955 27
1789719960 27
1789719965 27
1789719970 47
1789719975 47
1789719980 47
1789719985 47
1789719990 47
1789719995 64
1789720000 64
1789720005 64
1789720010 64
1789720015 64
1789720020 64
1789720025 64
1789720030 64
1789720035 64
1789720040 64
```
</details>

---

