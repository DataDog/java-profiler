---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 11:54:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795711868 96
1795711873 94
1795711878 94
1795711883 94
1795711888 94
1795711893 94
1795711898 94
1795711903 94
1795711908 94
1795711913 96
1795711918 96
1795711923 96
1795711928 96
1795711933 96
1795711938 96
1795711943 96
1795711948 96
1795711953 96
1795711958 96
1795711963 96
```
</details>

---

