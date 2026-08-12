---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 04:18:23 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
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
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1786522388 48
1786522393 48
1786522398 48
1786522403 48
1786522408 48
1786522413 48
1786522418 48
1786522423 48
1786522428 48
1786522433 48
1786522438 48
1786522443 48
1786522448 48
1786522453 48
1786522458 48
1786522463 48
1786522468 48
1786522473 48
1786522478 36
1786522483 36
```
</details>

---

