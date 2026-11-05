---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 11:16:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 7 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (4 unique values: 38-43 cores)</summary>

```
1793895013 41
1793895018 43
1793895023 43
1793895028 43
1793895033 43
1793895038 43
1793895043 43
1793895048 43
1793895053 43
1793895058 43
1793895063 40
1793895068 40
1793895073 38
1793895078 38
1793895083 38
1793895088 38
1793895093 38
1793895098 38
1793895103 38
1793895109 38
```
</details>

---

