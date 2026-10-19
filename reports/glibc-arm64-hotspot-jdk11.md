---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 12:22:24 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 8 |
| Allocations | 309 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1792426743 37
1792426748 37
1792426753 37
1792426758 37
1792426763 37
1792426768 37
1792426773 37
1792426778 37
1792426783 37
1792426788 37
1792426793 37
1792426798 37
1792426803 48
1792426808 48
1792426813 48
1792426818 48
1792426823 38
1792426828 38
1792426833 38
1792426838 38
```
</details>

---

