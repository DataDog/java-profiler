---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:15:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1794841848 25
1794841853 25
1794841858 25
1794841863 25
1794841868 25
1794841873 25
1794841878 25
1794841883 38
1794841888 38
1794841893 38
1794841898 38
1794841903 38
1794841908 38
1794841913 38
1794841918 38
1794841923 38
1794841928 38
1794841933 38
1794841938 38
1794841943 38
```
</details>

---

