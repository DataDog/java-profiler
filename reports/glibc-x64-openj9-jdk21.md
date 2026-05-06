---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-06 10:50:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (6 unique values: 69-79 cores)</summary>

```
1778078667 69
1778078672 69
1778078677 69
1778078682 69
1778078687 69
1778078692 69
1778078697 69
1778078702 69
1778078707 74
1778078712 74
1778078717 74
1778078722 74
1778078727 79
1778078732 79
1778078737 79
1778078742 78
1778078747 78
1778078752 78
1778078757 78
1778078762 75
```
</details>

---

