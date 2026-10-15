---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-15 10:59:07 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 16 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792075938 48
1792075943 48
1792075948 48
1792075953 48
1792075958 48
1792075963 48
1792075968 48
1792075973 48
1792075978 48
1792075983 48
1792075988 48
1792075993 48
1792075998 48
1792076003 48
1792076008 48
1792076013 43
1792076018 43
1792076023 43
1792076028 43
1792076033 43
```
</details>

---

