---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-01 15:37:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 11 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788291121 64
1788291126 64
1788291131 64
1788291136 64
1788291141 64
1788291146 59
1788291151 59
1788291156 59
1788291161 59
1788291166 59
1788291171 59
1788291176 59
1788291181 59
1788291186 59
1788291191 59
1788291196 59
1788291201 59
1788291206 59
1788291211 59
1788291216 59
```
</details>

---

