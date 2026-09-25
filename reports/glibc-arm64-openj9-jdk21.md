---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 06:49:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790333108 46
1790333113 46
1790333118 46
1790333123 46
1790333128 46
1790333133 46
1790333138 46
1790333143 46
1790333148 46
1790333153 46
1790333158 46
1790333163 48
1790333168 48
1790333173 46
1790333178 46
1790333183 46
1790333188 46
1790333193 46
1790333198 46
1790333203 46
```
</details>

---

