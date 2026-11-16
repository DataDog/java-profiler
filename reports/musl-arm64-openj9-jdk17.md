---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:21:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1794838612 42
1794838617 43
1794838622 43
1794838627 48
1794838632 48
1794838637 48
1794838642 48
1794838647 48
1794838652 48
1794838657 48
1794838662 48
1794838667 48
1794838672 48
1794838677 48
1794838682 48
1794838687 48
1794838692 48
1794838697 48
1794838702 48
1794838707 48
```
</details>

---

