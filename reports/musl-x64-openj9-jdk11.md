---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:33:08 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1033 |
| Sample Rate | 17.22/sec |
| Health Score | 1076% |
| Threads | 12 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (5 unique values: 73-79 cores)</summary>

```
1795011959 76
1795011964 76
1795011969 76
1795011974 76
1795011979 73
1795011985 73
1795011990 73
1795011995 75
1795012000 75
1795012005 75
1795012010 75
1795012015 75
1795012020 75
1795012025 75
1795012030 75
1795012035 75
1795012040 75
1795012045 77
1795012050 77
1795012055 77
```
</details>

---

