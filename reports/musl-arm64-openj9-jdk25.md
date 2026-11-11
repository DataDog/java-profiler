---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:26:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 14 |
| Allocations | 158 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794406947 43
1794406952 43
1794406957 43
1794406962 43
1794406967 43
1794406972 43
1794406977 43
1794406982 43
1794406987 43
1794406992 48
1794406997 48
1794407002 48
1794407007 48
1794407012 48
1794407017 48
1794407022 48
1794407027 48
1794407032 48
1794407037 48
1794407042 48
```
</details>

---

