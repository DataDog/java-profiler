---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:43:45 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 13 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 21-34 cores)</summary>

```
1794998140 34
1794998145 34
1794998150 34
1794998155 34
1794998160 34
1794998165 21
1794998170 21
1794998175 21
1794998180 21
1794998185 21
1794998190 21
1794998195 21
1794998200 21
1794998205 21
1794998210 21
1794998215 21
1794998220 21
1794998225 21
1794998230 21
1794998235 21
```
</details>

---

