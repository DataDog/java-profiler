---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-25 21:28:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 16-48 cores)</summary>

```
1792977805 16
1792977810 16
1792977815 16
1792977820 16
1792977825 16
1792977830 46
1792977835 46
1792977840 48
1792977845 48
1792977850 48
1792977855 48
1792977860 48
1792977865 48
1792977870 48
1792977875 48
1792977880 48
1792977885 48
1792977890 48
1792977895 48
1792977900 48
```
</details>

---

