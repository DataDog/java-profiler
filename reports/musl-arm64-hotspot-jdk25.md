---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-24 00:57:22 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787547188 64
1787547193 64
1787547198 64
1787547203 64
1787547208 64
1787547213 64
1787547218 64
1787547223 64
1787547228 64
1787547233 64
1787547238 64
1787547243 64
1787547248 64
1787547253 64
1787547258 64
1787547263 64
1787547268 64
1787547273 64
1787547278 64
1787547283 64
```
</details>

---

