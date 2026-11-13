---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:54:09 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794584962 48
1794584967 48
1794584972 48
1794584977 48
1794584982 48
1794584987 48
1794584992 48
1794584997 48
1794585002 48
1794585007 47
1794585012 47
1794585017 47
1794585022 47
1794585027 47
1794585032 47
1794585038 47
1794585043 47
1794585048 47
1794585053 47
1794585058 47
```
</details>

---

