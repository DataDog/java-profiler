---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:29:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 48-49 cores)</summary>

```
1789737728 48
1789737733 48
1789737738 48
1789737743 48
1789737748 48
1789737754 48
1789737759 49
1789737764 49
1789737769 49
1789737774 49
1789737779 49
1789737784 49
1789737789 49
1789737794 49
1789737799 49
1789737804 49
1789737809 49
1789737814 49
1789737819 49
1789737824 49
```
</details>

---

