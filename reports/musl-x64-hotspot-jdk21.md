---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 08:26:52 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 10-38 cores)</summary>

```
1795785643 10
1795785648 10
1795785653 10
1795785658 10
1795785663 38
1795785668 38
1795785673 33
1795785678 33
1795785683 33
1795785688 33
1795785693 33
1795785698 33
1795785703 33
1795785708 33
1795785713 33
1795785718 33
1795785723 33
1795785728 33
1795785733 33
1795785738 33
```
</details>

---

