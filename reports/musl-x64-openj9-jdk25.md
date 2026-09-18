---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:31:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 9-56 cores)</summary>

```
1789719948 9
1789719953 9
1789719958 9
1789719963 9
1789719968 9
1789719973 9
1789719978 9
1789719983 9
1789719988 9
1789719993 9
1789719998 9
1789720003 9
1789720008 9
1789720013 9
1789720018 9
1789720023 9
1789720028 9
1789720033 9
1789720038 56
1789720043 56
```
</details>

---

