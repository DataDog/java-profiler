---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 09:37:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1794839610 88
1794839615 88
1794839620 88
1794839625 88
1794839630 88
1794839635 88
1794839640 88
1794839645 88
1794839650 88
1794839655 88
1794839660 88
1794839665 84
1794839670 84
1794839675 84
1794839680 84
1794839685 84
1794839690 84
1794839695 84
1794839700 84
1794839705 84
```
</details>

---

