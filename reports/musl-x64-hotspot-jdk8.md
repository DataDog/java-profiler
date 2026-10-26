---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-26 08:33:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 79-84 cores)</summary>

```
1793017739 84
1793017744 84
1793017749 84
1793017754 84
1793017759 84
1793017764 84
1793017769 84
1793017774 84
1793017779 84
1793017784 84
1793017789 84
1793017794 84
1793017799 81
1793017804 81
1793017809 81
1793017814 81
1793017819 81
1793017824 81
1793017829 79
1793017834 79
```
</details>

---

