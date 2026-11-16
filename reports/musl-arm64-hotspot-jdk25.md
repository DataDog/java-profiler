---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:30:11 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 43 |
| Sample Rate | 0.72/sec |
| Health Score | 45% |
| Threads | 7 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 12 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794831918 47
1794831923 47
1794831928 48
1794831933 48
1794831938 48
1794831943 48
1794831948 48
1794831953 48
1794831958 48
1794831963 48
1794831968 48
1794831973 48
1794831978 48
1794831983 48
1794831988 48
1794831993 48
1794831998 48
1794832003 48
1794832008 48
1794832013 48
```
</details>

---

