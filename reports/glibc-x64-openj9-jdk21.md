---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 15:10:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1792523040 84
1792523045 84
1792523050 84
1792523055 84
1792523060 84
1792523065 84
1792523070 84
1792523075 84
1792523080 84
1792523085 84
1792523090 84
1792523095 84
1792523100 84
1792523105 84
1792523110 86
1792523115 86
1792523120 86
1792523125 88
1792523130 88
1792523135 88
```
</details>

---

