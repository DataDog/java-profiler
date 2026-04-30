---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:06:55 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 64-75 cores)</summary>

```
1777557717 75
1777557722 75
1777557727 74
1777557732 74
1777557737 74
1777557742 74
1777557747 74
1777557752 74
1777557757 69
1777557762 69
1777557767 69
1777557772 69
1777557777 69
1777557782 69
1777557787 69
1777557792 69
1777557797 69
1777557802 69
1777557807 69
1777557812 67
```
</details>

---

