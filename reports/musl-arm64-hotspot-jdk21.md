---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 14:59:55 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
1793040935 39
1793040940 39
1793040945 39
1793040950 39
1793040955 34
1793040960 34
1793040965 34
1793040970 34
1793040975 34
1793040980 34
1793040985 34
1793040990 34
1793040995 34
1793041000 34
1793041005 34
1793041011 34
1793041016 34
1793041021 39
1793041026 39
1793041031 39
```
</details>

---

