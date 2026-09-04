---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-04 14:55:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788547866 64
1788547871 64
1788547876 64
1788547881 64
1788547886 59
1788547891 59
1788547896 59
1788547901 59
1788547906 59
1788547911 59
1788547916 59
1788547921 59
1788547926 59
1788547931 59
1788547936 59
1788547941 59
1788547946 59
1788547951 64
1788547956 64
1788547962 64
```
</details>

---

