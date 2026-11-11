---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:26:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 11 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1794406985 44
1794406990 44
1794406995 44
1794407000 44
1794407005 44
1794407010 44
1794407015 44
1794407020 44
1794407025 44
1794407030 44
1794407035 44
1794407040 46
1794407045 46
1794407050 46
1794407056 46
1794407061 46
1794407066 46
1794407071 46
1794407076 46
1794407081 46
```
</details>

---

