---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 10:00:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 11 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790258094 50
1790258099 50
1790258104 50
1790258109 50
1790258114 50
1790258119 50
1790258124 50
1790258129 50
1790258134 50
1790258139 45
1790258144 45
1790258149 45
1790258154 45
1790258159 45
1790258165 45
1790258170 45
1790258175 45
1790258180 50
1790258185 50
1790258190 50
```
</details>

---

