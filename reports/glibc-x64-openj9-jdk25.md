---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:26:51 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 23-26 cores)</summary>

```
1795785640 24
1795785645 26
1795785650 26
1795785655 26
1795785660 26
1795785665 26
1795785670 26
1795785675 26
1795785680 26
1795785685 26
1795785690 26
1795785695 26
1795785700 26
1795785705 26
1795785710 26
1795785715 26
1795785720 26
1795785725 26
1795785730 26
1795785735 23
```
</details>

---

