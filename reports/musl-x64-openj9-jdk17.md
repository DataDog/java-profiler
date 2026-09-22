---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:47:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 900 |
| Sample Rate | 15.00/sec |
| Health Score | 938% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 63-90 cores)</summary>

```
1790091672 63
1790091677 63
1790091682 63
1790091687 63
1790091692 63
1790091697 63
1790091702 63
1790091707 63
1790091712 65
1790091717 65
1790091722 65
1790091727 65
1790091732 65
1790091737 65
1790091742 65
1790091747 65
1790091752 65
1790091757 65
1790091762 65
1790091767 65
```
</details>

---

