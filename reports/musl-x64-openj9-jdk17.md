---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:29:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 11-24 cores)</summary>

```
1795001033 11
1795001038 11
1795001043 11
1795001048 11
1795001053 11
1795001058 11
1795001063 11
1795001068 11
1795001073 11
1795001078 11
1795001083 11
1795001088 24
1795001093 24
1795001098 24
1795001103 24
1795001108 24
1795001113 24
1795001118 24
1795001123 24
1795001128 24
```
</details>

---

