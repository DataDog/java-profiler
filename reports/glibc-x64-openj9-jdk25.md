---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:35:23 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 52-96 cores)</summary>

```
1794396664 74
1794396669 74
1794396674 74
1794396679 74
1794396684 74
1794396689 74
1794396694 74
1794396699 96
1794396704 96
1794396709 96
1794396714 96
1794396719 52
1794396724 52
1794396729 52
1794396734 52
1794396739 52
1794396744 52
1794396749 52
1794396754 52
1794396759 52
```
</details>

---

