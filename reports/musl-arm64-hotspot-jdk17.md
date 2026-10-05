---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 00:55:42 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791175916 51
1791175921 51
1791175926 51
1791175931 51
1791175936 51
1791175941 51
1791175946 51
1791175951 64
1791175956 64
1791175962 64
1791175967 64
1791175972 64
1791175977 64
1791175982 64
1791175987 64
1791175992 64
1791175997 64
1791176002 64
1791176007 64
1791176012 64
```
</details>

---

