---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-26 06:26:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 67-79 cores)</summary>

```
1779790809 71
1779790814 71
1779790819 71
1779790824 67
1779790829 67
1779790834 67
1779790839 67
1779790844 67
1779790849 67
1779790854 67
1779790859 67
1779790864 67
1779790869 67
1779790874 72
1779790879 72
1779790884 74
1779790889 74
1779790894 74
1779790899 79
1779790904 79
```
</details>

---

