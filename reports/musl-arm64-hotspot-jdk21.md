---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-17 14:25:53 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 14 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 30-48 cores)</summary>

```
1786990889 30
1786990894 30
1786990899 30
1786990904 30
1786990909 30
1786990914 30
1786990919 30
1786990924 30
1786990929 30
1786990934 30
1786990939 30
1786990944 30
1786990949 30
1786990954 30
1786990960 30
1786990965 39
1786990970 39
1786990975 39
1786990980 48
1786990985 48
```
</details>

---

