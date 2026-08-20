---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 12:31:54 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787243203 64
1787243208 64
1787243213 64
1787243218 64
1787243223 64
1787243228 64
1787243233 64
1787243238 64
1787243243 64
1787243248 64
1787243253 64
1787243258 64
1787243263 64
1787243268 64
1787243273 64
1787243278 64
1787243283 64
1787243288 64
1787243293 64
1787243298 64
```
</details>

---

