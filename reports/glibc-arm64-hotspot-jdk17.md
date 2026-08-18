---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787063138 64
1787063143 64
1787063148 64
1787063153 64
1787063158 64
1787063163 64
1787063168 64
1787063173 64
1787063178 64
1787063183 64
1787063188 64
1787063193 64
1787063198 64
1787063203 64
1787063208 64
1787063213 64
1787063218 64
1787063223 64
1787063228 59
1787063233 59
```
</details>

---

