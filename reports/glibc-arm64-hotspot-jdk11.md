---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:08:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 11 |
| Allocations | 206 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777475083 64
1777475088 64
1777475093 64
1777475098 64
1777475103 64
1777475108 64
1777475113 64
1777475118 64
1777475123 64
1777475128 64
1777475133 64
1777475138 64
1777475143 64
1777475148 64
1777475153 64
1777475158 64
1777475163 64
1777475168 64
1777475173 64
1777475178 64
```
</details>

---

