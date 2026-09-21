---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:47:05 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1789979896 38
1789979901 38
1789979906 38
1789979911 38
1789979916 38
1789979921 38
1789979926 38
1789979931 38
1789979936 38
1789979941 43
1789979946 43
1789979951 43
1789979956 43
1789979961 41
1789979966 41
1789979971 41
1789979976 41
1789979981 41
1789979986 41
1789979991 41
```
</details>

---

