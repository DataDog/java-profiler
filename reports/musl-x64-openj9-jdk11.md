---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 17:08:16 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1792443740 29
1792443745 29
1792443750 29
1792443755 29
1792443760 29
1792443765 29
1792443770 29
1792443775 29
1792443780 29
1792443785 29
1792443790 29
1792443795 29
1792443800 29
1792443805 29
1792443810 29
1792443815 29
1792443820 29
1792443825 29
1792443830 32
1792443835 32
```
</details>

---

