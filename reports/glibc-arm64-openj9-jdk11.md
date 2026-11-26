---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 11:54:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795711847 33
1795711852 33
1795711858 33
1795711863 33
1795711868 33
1795711873 33
1795711878 33
1795711883 33
1795711888 33
1795711893 33
1795711898 33
1795711903 33
1795711908 33
1795711913 33
1795711918 33
1795711923 33
1795711928 64
1795711933 64
1795711938 33
1795711943 33
```
</details>

---

