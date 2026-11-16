---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 07:42:01 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 79-84 cores)</summary>

```
1794832698 82
1794832703 82
1794832708 82
1794832713 82
1794832718 82
1794832723 82
1794832728 82
1794832733 82
1794832738 82
1794832743 84
1794832748 84
1794832753 81
1794832758 81
1794832763 79
1794832768 79
1794832773 79
1794832778 79
1794832783 79
1794832788 79
1794832793 79
```
</details>

---

