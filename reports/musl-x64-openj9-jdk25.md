---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 18:32:13 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1085 |
| Sample Rate | 18.08/sec |
| Health Score | 1130% |
| Threads | 12 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 71-76 cores)</summary>

```
1778538449 71
1778538454 71
1778538459 71
1778538464 71
1778538469 71
1778538474 71
1778538479 71
1778538484 71
1778538489 71
1778538494 71
1778538499 76
1778538504 76
1778538509 76
1778538514 76
1778538519 76
1778538524 76
1778538529 76
1778538534 76
1778538539 76
1778538544 76
```
</details>

---

