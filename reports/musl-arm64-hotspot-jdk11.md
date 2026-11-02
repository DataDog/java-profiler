---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-01 20:32:52 EST

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
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793582718 64
1793582723 64
1793582728 64
1793582734 64
1793582739 64
1793582744 64
1793582749 64
1793582754 64
1793582759 64
1793582764 64
1793582769 64
1793582774 64
1793582779 64
1793582784 64
1793582789 64
1793582794 64
1793582799 64
1793582804 64
1793582809 64
1793582814 64
```
</details>

---

