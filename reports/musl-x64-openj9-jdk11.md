---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-16 12:11:40 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 16-32 cores)</summary>

```
1789574738 16
1789574743 16
1789574748 16
1789574754 16
1789574759 16
1789574764 16
1789574769 16
1789574774 16
1789574779 16
1789574784 16
1789574789 16
1789574794 32
1789574799 32
1789574804 32
1789574809 32
1789574814 32
1789574819 32
1789574824 32
1789574829 32
1789574834 32
```
</details>

---

