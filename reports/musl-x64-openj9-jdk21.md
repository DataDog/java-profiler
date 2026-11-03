---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 12:51:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 10-32 cores)</summary>

```
1793727946 10
1793727951 10
1793727956 10
1793727961 10
1793727966 10
1793727971 10
1793727976 10
1793727981 10
1793727986 10
1793727991 10
1793727996 10
1793728001 10
1793728006 10
1793728011 32
1793728016 32
1793728021 10
1793728026 10
1793728031 10
1793728036 10
1793728041 10
```
</details>

---

