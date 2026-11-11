---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:54:43 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794433792 48
1794433797 48
1794433802 48
1794433807 48
1794433812 48
1794433817 48
1794433822 48
1794433827 48
1794433832 48
1794433837 48
1794433842 48
1794433847 48
1794433852 48
1794433857 48
1794433862 48
1794433867 48
1794433872 48
1794433877 48
1794433882 48
1794433887 48
```
</details>

---

