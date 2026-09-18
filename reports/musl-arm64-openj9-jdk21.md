---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:49:03 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 10 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 20-30 cores)</summary>

```
1789731840 30
1789731845 30
1789731850 20
1789731855 20
1789731860 20
1789731865 20
1789731870 20
1789731875 20
1789731880 20
1789731885 20
1789731890 20
1789731895 20
1789731900 20
1789731905 20
1789731910 20
1789731915 25
1789731920 25
1789731925 25
1789731930 25
1789731935 25
```
</details>

---

