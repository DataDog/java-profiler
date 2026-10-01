---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 08:19:06 EDT

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 9 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 34-47 cores)</summary>

```
1790856851 34
1790856856 34
1790856861 34
1790856866 34
1790856871 34
1790856876 34
1790856881 34
1790856886 34
1790856891 34
1790856896 34
1790856901 34
1790856906 34
1790856911 38
1790856916 38
1790856921 43
1790856926 43
1790856931 47
1790856936 47
1790856941 47
1790856946 47
```
</details>

---

