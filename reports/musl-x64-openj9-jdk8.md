---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-20 07:23:23 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1787224725 64
1787224730 64
1787224735 56
1787224740 56
1787224745 56
1787224750 56
1787224755 56
1787224760 56
1787224765 56
1787224770 56
1787224775 56
1787224780 56
1787224785 56
1787224790 56
1787224795 56
1787224800 56
1787224805 56
1787224810 56
1787224815 56
1787224820 56
```
</details>

---

