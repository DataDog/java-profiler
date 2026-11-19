---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 11 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 15 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795108870 48
1795108875 48
1795108880 48
1795108885 48
1795108890 50
1795108895 50
1795108900 50
1795108905 64
1795108910 64
1795108915 64
1795108920 64
1795108926 64
1795108931 64
1795108936 64
1795108941 64
1795108946 64
1795108951 64
1795108956 64
1795108961 64
1795108966 64
```
</details>

---

