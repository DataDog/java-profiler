---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:22:23 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 32-52 cores)</summary>

```
1795429067 52
1795429072 52
1795429077 52
1795429082 37
1795429088 37
1795429093 37
1795429098 37
1795429103 37
1795429108 37
1795429113 37
1795429118 37
1795429123 37
1795429128 37
1795429133 32
1795429138 32
1795429143 32
1795429148 32
1795429153 32
1795429158 32
1795429163 32
```
</details>

---

