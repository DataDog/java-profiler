---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 08:21:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 28-40 cores)</summary>

```
1795698962 28
1795698967 28
1795698972 34
1795698977 34
1795698982 34
1795698987 34
1795698992 34
1795698997 34
1795699002 34
1795699007 34
1795699012 40
1795699017 40
1795699022 40
1795699027 40
1795699032 40
1795699037 40
1795699042 40
1795699047 40
1795699052 40
1795699057 40
```
</details>

---

