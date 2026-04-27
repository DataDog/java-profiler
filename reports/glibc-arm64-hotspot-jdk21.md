---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-26 21:26:01 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777252587 32
1777252592 32
1777252597 32
1777252602 32
1777252607 32
1777252612 32
1777252617 32
1777252622 32
1777252627 32
1777252632 32
1777252637 32
1777252642 32
1777252647 32
1777252652 32
1777252657 32
1777252662 32
1777252667 32
1777252672 32
1777252677 32
1777252682 32
```
</details>

---

