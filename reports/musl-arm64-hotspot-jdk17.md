---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 05:51:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1795517203 47
1795517208 47
1795517213 47
1795517218 47
1795517223 47
1795517228 52
1795517233 52
1795517238 52
1795517243 52
1795517248 52
1795517253 52
1795517258 52
1795517263 52
1795517268 52
1795517273 52
1795517278 52
1795517283 52
1795517288 52
1795517293 52
1795517298 64
```
</details>

---

