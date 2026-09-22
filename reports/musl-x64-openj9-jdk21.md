---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 07:06:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 12 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1790074835 76
1790074840 76
1790074845 76
1790074850 76
1790074855 76
1790074860 76
1790074865 76
1790074870 76
1790074875 76
1790074880 76
1790074885 68
1790074890 68
1790074895 68
1790074900 68
1790074905 68
1790074910 68
1790074915 68
1790074920 68
1790074925 68
1790074930 68
```
</details>

---

