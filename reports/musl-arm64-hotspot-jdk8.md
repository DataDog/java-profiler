---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-12 05:20:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1786526138 27
1786526143 27
1786526148 27
1786526153 27
1786526158 32
1786526163 32
1786526168 32
1786526173 32
1786526178 32
1786526183 32
1786526188 30
1786526193 30
1786526198 30
1786526203 30
1786526208 30
1786526213 30
1786526218 30
1786526223 30
1786526228 30
1786526233 30
```
</details>

---

