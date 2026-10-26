---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-26 06:57:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 17-20 cores)</summary>

```
1793012000 20
1793012005 20
1793012010 20
1793012015 20
1793012020 20
1793012025 20
1793012030 20
1793012035 20
1793012040 20
1793012045 17
1793012050 17
1793012055 17
1793012060 17
1793012065 17
1793012070 17
1793012075 17
1793012080 17
1793012085 17
1793012090 17
1793012095 17
```
</details>

---

