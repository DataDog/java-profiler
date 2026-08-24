---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-24 15:44:28 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 33-34 cores)</summary>

```
1787600211 34
1787600216 34
1787600221 34
1787600226 33
1787600231 33
1787600236 33
1787600241 33
1787600246 33
1787600251 33
1787600256 34
1787600261 34
1787600266 34
1787600271 34
1787600276 34
1787600281 34
1787600286 34
1787600291 34
1787600296 34
1787600301 34
1787600306 34
```
</details>

---

