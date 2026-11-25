---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 03:20:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 41-51 cores)</summary>

```
1795594643 41
1795594648 51
1795594654 51
1795594659 51
1795594664 51
1795594669 51
1795594674 51
1795594679 51
1795594684 51
1795594689 51
1795594694 51
1795594699 51
1795594704 51
1795594709 51
1795594714 51
1795594719 51
1795594724 51
1795594729 51
1795594734 51
1795594739 51
```
</details>

---

