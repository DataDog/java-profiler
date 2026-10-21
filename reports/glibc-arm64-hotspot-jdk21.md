---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 07:16:21 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792581098 64
1792581103 64
1792581108 64
1792581113 64
1792581118 64
1792581123 64
1792581128 64
1792581133 51
1792581138 51
1792581143 51
1792581148 51
1792581153 51
1792581158 51
1792581163 51
1792581168 51
1792581173 51
1792581178 51
1792581183 51
1792581188 51
1792581193 51
```
</details>

---

