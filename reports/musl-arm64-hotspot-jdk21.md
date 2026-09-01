---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:37:53 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788291122 64
1788291127 64
1788291132 64
1788291137 64
1788291142 64
1788291147 59
1788291152 59
1788291157 59
1788291162 59
1788291167 59
1788291172 59
1788291177 59
1788291182 59
1788291187 59
1788291192 59
1788291197 59
1788291202 59
1788291207 59
1788291212 59
1788291217 59
```
</details>

---

