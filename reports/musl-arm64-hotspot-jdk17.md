---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 05:51:52 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 14 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787132858 34
1787132863 34
1787132868 34
1787132873 34
1787132878 34
1787132883 34
1787132888 34
1787132893 34
1787132898 34
1787132903 34
1787132908 34
1787132913 34
1787132918 34
1787132923 34
1787132928 34
1787132933 34
1787132938 34
1787132943 34
1787132948 34
1787132953 29
```
</details>

---

