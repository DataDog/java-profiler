---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:35:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 11 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 16-24 cores)</summary>

```
1790332127 16
1790332132 16
1790332137 16
1790332142 16
1790332147 16
1790332152 16
1790332157 16
1790332163 16
1790332168 16
1790332173 16
1790332178 24
1790332183 24
1790332188 24
1790332193 24
1790332198 24
1790332203 24
1790332208 19
1790332213 19
1790332218 19
1790332223 19
```
</details>

---

