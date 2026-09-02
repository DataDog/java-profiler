---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 13:35:50 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788369975 34
1788369980 34
1788369985 34
1788369990 34
1788369995 34
1788370000 29
1788370005 29
1788370010 29
1788370015 29
1788370020 29
1788370025 29
1788370030 29
1788370035 29
1788370040 29
1788370045 29
1788370050 29
1788370055 29
1788370060 29
1788370065 29
1788370070 29
```
</details>

---

