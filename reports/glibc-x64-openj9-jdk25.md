---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:31:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 12 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 74-85 cores)</summary>

```
1795012055 85
1795012060 85
1795012065 85
1795012070 85
1795012075 85
1795012080 85
1795012085 85
1795012090 85
1795012095 85
1795012100 85
1795012105 74
1795012110 74
1795012115 83
1795012120 83
1795012125 83
1795012130 83
1795012135 83
1795012140 83
1795012145 83
1795012150 83
```
</details>

---

