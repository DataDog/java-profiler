---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 07:05:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1795608069 46
1795608074 46
1795608079 46
1795608084 46
1795608089 46
1795608094 46
1795608099 48
1795608104 48
1795608109 48
1795608114 48
1795608120 48
1795608125 48
1795608130 48
1795608135 48
1795608140 48
1795608145 48
1795608150 48
1795608155 48
1795608160 48
1795608165 48
```
</details>

---

