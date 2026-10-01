---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 08:19:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 54-57 cores)</summary>

```
1790856846 54
1790856851 54
1790856856 54
1790856861 54
1790856866 54
1790856871 57
1790856876 57
1790856881 57
1790856886 57
1790856891 57
1790856896 57
1790856901 57
1790856906 57
1790856911 57
1790856916 57
1790856921 57
1790856926 57
1790856931 57
1790856936 57
1790856941 57
```
</details>

---

