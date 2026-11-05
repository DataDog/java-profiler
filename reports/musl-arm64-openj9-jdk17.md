---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 11:16:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
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
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793895013 48
1793895018 48
1793895023 48
1793895028 48
1793895033 48
1793895038 48
1793895043 48
1793895048 48
1793895053 48
1793895058 48
1793895063 48
1793895068 48
1793895073 48
1793895078 48
1793895083 48
1793895088 48
1793895093 48
1793895098 48
1793895103 48
1793895108 48
```
</details>

---

