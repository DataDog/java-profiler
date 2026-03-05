---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-05 13:28:45 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 12 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1772734942 28
1772734947 28
1772734952 28
1772734957 28
1772734962 28
1772734967 28
1772734972 28
1772734977 28
1772734982 28
1772734987 28
1772734992 28
1772734997 28
1772735002 28
1772735007 28
1772735012 32
1772735017 32
1772735022 29
1772735027 29
1772735032 29
1772735037 29
```
</details>

---

