---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:38:42 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770125661 32
1770125666 32
1770125671 32
1770125676 32
1770125681 32
1770125686 32
1770125691 32
1770125696 32
1770125701 32
1770125706 32
1770125711 32
1770125716 32
1770125721 32
1770125726 32
1770125731 32
1770125736 32
1770125741 32
1770125746 32
1770125751 32
1770125756 32
```
</details>

---

