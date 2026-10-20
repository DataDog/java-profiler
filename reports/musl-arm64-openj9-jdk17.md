---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 14:00:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (4 unique values: 44-64 cores)</summary>

```
1792518943 46
1792518948 46
1792518953 46
1792518958 46
1792518963 51
1792518968 51
1792518973 51
1792518978 51
1792518983 51
1792518988 51
1792518993 51
1792518998 51
1792519003 51
1792519008 51
1792519013 51
1792519018 51
1792519023 51
1792519028 51
1792519033 51
1792519038 51
```
</details>

---

