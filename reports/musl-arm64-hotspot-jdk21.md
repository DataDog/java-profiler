---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:35:11 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 35-47 cores)</summary>

```
1794357037 35
1794357042 35
1794357047 47
1794357052 47
1794357057 47
1794357062 47
1794357067 42
1794357072 42
1794357077 42
1794357082 42
1794357087 42
1794357092 42
1794357097 42
1794357102 42
1794357107 47
1794357112 47
1794357117 47
1794357122 47
1794357127 47
1794357132 47
```
</details>

---

