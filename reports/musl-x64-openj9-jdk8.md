---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 09:37:47 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
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
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1794839609 72
1794839614 72
1794839619 72
1794839624 72
1794839629 74
1794839634 74
1794839639 74
1794839644 76
1794839649 76
1794839654 76
1794839659 76
1794839664 76
1794839669 76
1794839674 76
1794839679 76
1794839684 76
1794839689 76
1794839694 76
1794839699 76
1794839704 76
```
</details>

---

