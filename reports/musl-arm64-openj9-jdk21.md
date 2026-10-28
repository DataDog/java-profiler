---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 05:04:15 EDT

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
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 11 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793177977 48
1793177982 48
1793177987 48
1793177992 48
1793177997 48
1793178002 48
1793178007 48
1793178012 48
1793178017 48
1793178022 48
1793178027 48
1793178032 48
1793178037 48
1793178042 48
1793178047 48
1793178052 48
1793178057 48
1793178062 48
1793178067 48
1793178072 48
```
</details>

---

