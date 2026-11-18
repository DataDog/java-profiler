---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:43:45 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794998140 34
1794998145 34
1794998150 34
1794998155 34
1794998160 34
1794998165 34
1794998170 34
1794998175 34
1794998180 34
1794998185 34
1794998190 34
1794998195 34
1794998200 34
1794998205 34
1794998210 34
1794998215 34
1794998220 34
1794998225 34
1794998230 34
1794998235 29
```
</details>

---

