---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:49:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1024 |
| Sample Rate | 17.07/sec |
| Health Score | 1067% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790332974 50
1790332979 50
1790332984 50
1790332989 50
1790332994 50
1790332999 50
1790333004 50
1790333009 50
1790333014 50
1790333019 50
1790333024 50
1790333029 50
1790333034 50
1790333039 50
1790333044 50
1790333049 50
1790333054 50
1790333059 50
1790333064 50
1790333069 50
```
</details>

---

