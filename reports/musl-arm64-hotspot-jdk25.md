---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 15:09:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 13 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (4 unique values: 31-41 cores)</summary>

```
1786474961 34
1786474966 34
1786474971 34
1786474976 36
1786474981 36
1786474986 36
1786474991 31
1786474996 31
1786475001 31
1786475006 31
1786475011 36
1786475016 36
1786475021 36
1786475026 36
1786475031 36
1786475036 36
1786475041 41
1786475046 41
1786475051 41
1786475056 41
```
</details>

---

