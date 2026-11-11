---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:35:11 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 14 |
| Allocations | 176 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794357047 43
1794357052 43
1794357057 43
1794357062 43
1794357067 43
1794357072 43
1794357077 43
1794357082 43
1794357087 43
1794357092 43
1794357097 43
1794357102 43
1794357107 43
1794357112 43
1794357117 43
1794357122 43
1794357127 43
1794357132 43
1794357137 43
1794357142 43
```
</details>

---

