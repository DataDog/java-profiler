---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:31:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1795012045 62
1795012050 62
1795012055 62
1795012060 62
1795012065 62
1795012070 62
1795012075 62
1795012080 62
1795012085 62
1795012090 62
1795012095 60
1795012100 60
1795012105 60
1795012110 60
1795012115 62
1795012120 62
1795012125 62
1795012130 62
1795012135 62
1795012140 62
```
</details>

---

