---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-21 10:44:44 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 43-45 cores)</summary>

```
1787323179 45
1787323184 45
1787323189 45
1787323194 45
1787323199 45
1787323204 45
1787323209 45
1787323214 45
1787323219 45
1787323224 43
1787323229 43
1787323234 43
1787323239 43
1787323244 43
1787323249 43
1787323254 43
1787323259 43
1787323264 43
1787323269 43
1787323274 45
```
</details>

---

