---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-24 15:44:29 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 10 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1787600249 64
1787600254 64
1787600259 64
1787600264 64
1787600269 64
1787600274 64
1787600279 64
1787600284 64
1787600289 64
1787600294 64
1787600299 64
1787600304 64
1787600309 64
1787600314 64
1787600319 64
1787600324 64
1787600329 64
1787600334 64
1787600339 64
1787600344 64
```
</details>

---

