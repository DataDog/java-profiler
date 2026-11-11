---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:26:48 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 20-30 cores)</summary>

```
1794406947 22
1794406952 22
1794406957 22
1794406962 22
1794406967 22
1794406972 22
1794406977 22
1794406982 22
1794406987 22
1794406992 20
1794406997 20
1794407002 20
1794407007 20
1794407012 20
1794407017 20
1794407022 30
1794407027 30
1794407032 30
1794407037 30
1794407042 30
```
</details>

---

