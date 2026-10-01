---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 08:19:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1790856866 39
1790856871 39
1790856876 39
1790856881 39
1790856886 39
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
1790856956 48
1790856961 48
```
</details>

---

