---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 07:26:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1792408928 36
1792408933 36
1792408938 36
1792408943 36
1792408948 36
1792408954 36
1792408959 36
1792408964 36
1792408969 36
1792408974 36
1792408979 36
1792408984 36
1792408989 36
1792408994 36
1792408999 36
1792409004 36
1792409009 31
1792409014 31
1792409019 31
1792409024 31
```
</details>

---

