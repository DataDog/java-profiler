---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-11-27 08:26:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 3 |
| Sample Rate | 0.05/sec |
| Health Score | 3% |
| Threads | 2 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1795785654 56
1795785659 56
1795785664 56
1795785670 56
1795785675 56
1795785680 56
1795785685 56
1795785690 56
1795785695 56
1795785700 56
1795785705 56
1795785710 56
1795785715 56
1795785720 56
1795785725 56
1795785730 56
1795785735 56
1795785740 56
1795785745 56
1795785750 56
```
</details>

---

