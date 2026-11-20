---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:40:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 12 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1795192476 49
1795192481 49
1795192486 49
1795192491 49
1795192496 49
1795192501 49
1795192506 49
1795192511 49
1795192516 49
1795192521 49
1795192526 49
1795192531 49
1795192536 49
1795192541 49
1795192546 49
1795192551 49
1795192556 49
1795192561 64
1795192566 64
1795192571 64
```
</details>

---

