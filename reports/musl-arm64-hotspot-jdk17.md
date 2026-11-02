---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 30-64 cores)</summary>

```
1793656888 30
1793656893 30
1793656898 30
1793656903 30
1793656908 30
1793656913 30
1793656918 30
1793656923 30
1793656928 30
1793656933 30
1793656938 30
1793656943 30
1793656948 30
1793656953 30
1793656958 30
1793656963 30
1793656968 30
1793656973 30
1793656978 30
1793656983 64
```
</details>

---

