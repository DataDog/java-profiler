---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 13:22:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795198614 44
1795198619 44
1795198624 44
1795198629 44
1795198634 44
1795198639 44
1795198644 44
1795198649 44
1795198654 44
1795198659 64
1795198664 64
1795198669 64
1795198674 49
1795198679 49
1795198684 49
1795198689 49
1795198694 49
1795198700 49
1795198705 49
1795198710 49
```
</details>

---

