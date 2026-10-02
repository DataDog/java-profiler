---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-02 12:03:21 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 88-93 cores)</summary>

```
1790956704 88
1790956709 88
1790956714 88
1790956719 88
1790956724 88
1790956729 88
1790956734 88
1790956739 88
1790956744 88
1790956749 88
1790956754 88
1790956759 88
1790956764 93
1790956769 93
1790956774 93
1790956779 93
1790956784 93
1790956789 93
1790956794 93
1790956799 93
```
</details>

---

