---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 12:10:02 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777392261 64
1777392266 64
1777392271 64
1777392276 64
1777392281 64
1777392286 64
1777392291 64
1777392296 64
1777392301 64
1777392306 64
1777392311 64
1777392316 64
1777392321 64
1777392326 64
1777392331 64
1777392337 64
1777392342 64
1777392347 64
1777392352 64
1777392357 64
```
</details>

---

