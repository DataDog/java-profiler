---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:07:50 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 26-46 cores)</summary>

```
1794394998 46
1794395003 46
1794395008 26
1794395013 26
1794395018 26
1794395023 26
1794395028 26
1794395033 26
1794395038 26
1794395043 26
1794395048 31
1794395053 31
1794395058 31
1794395063 31
1794395068 26
1794395073 26
1794395078 26
1794395083 26
1794395088 26
1794395093 26
```
</details>

---

