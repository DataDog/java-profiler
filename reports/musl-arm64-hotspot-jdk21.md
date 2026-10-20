---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 05:55:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 9 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792489857 48
1792489862 48
1792489867 48
1792489873 48
1792489878 48
1792489883 48
1792489888 48
1792489893 43
1792489898 43
1792489903 43
1792489908 43
1792489913 43
1792489918 43
1792489923 43
1792489928 43
1792489933 38
1792489938 38
1792489943 38
1792489948 38
1792489953 38
```
</details>

---

