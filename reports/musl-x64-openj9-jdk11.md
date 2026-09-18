---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:29:46 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1789712713 58
1789712718 58
1789712723 58
1789712728 58
1789712733 58
1789712738 58
1789712743 58
1789712748 58
1789712753 58
1789712758 58
1789712763 58
1789712768 58
1789712773 58
1789712778 58
1789712783 58
1789712788 58
1789712793 56
1789712798 56
1789712803 56
1789712808 56
```
</details>

---

