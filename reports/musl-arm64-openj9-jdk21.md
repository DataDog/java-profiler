---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 08:19:06 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790856856 44
1790856861 44
1790856866 48
1790856871 48
1790856876 48
1790856881 48
1790856886 48
1790856891 48
1790856896 48
1790856901 48
1790856906 48
1790856911 48
1790856916 48
1790856921 48
1790856926 48
1790856931 48
1790856936 48
1790856941 48
1790856946 48
1790856951 48
```
</details>

---

