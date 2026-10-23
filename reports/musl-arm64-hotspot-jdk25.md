---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:56:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1792767098 38
1792767103 38
1792767108 38
1792767113 38
1792767118 38
1792767123 38
1792767128 38
1792767133 38
1792767138 38
1792767143 38
1792767148 38
1792767153 43
1792767158 43
1792767163 41
1792767168 41
1792767173 41
1792767178 41
1792767183 41
1792767188 41
1792767193 41
```
</details>

---

