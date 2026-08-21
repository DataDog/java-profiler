---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 11:01:08 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1787324191 48
1787324196 48
1787324201 48
1787324206 48
1787324211 47
1787324216 47
1787324221 42
1787324226 42
1787324231 42
1787324236 42
1787324241 43
1787324246 43
1787324251 43
1787324256 43
1787324261 43
1787324266 43
1787324271 48
1787324276 48
1787324281 48
1787324286 48
```
</details>

---

