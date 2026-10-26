---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-25 21:28:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 66-79 cores)</summary>

```
1792977840 79
1792977845 79
1792977850 77
1792977855 77
1792977860 77
1792977865 77
1792977870 77
1792977875 79
1792977880 79
1792977885 79
1792977890 79
1792977895 79
1792977900 79
1792977905 79
1792977910 79
1792977915 79
1792977920 79
1792977925 75
1792977930 75
1792977935 75
```
</details>

---

