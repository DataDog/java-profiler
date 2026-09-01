---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:03:50 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 15 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788289117 64
1788289122 64
1788289127 64
1788289132 64
1788289137 64
1788289142 64
1788289147 64
1788289152 64
1788289157 64
1788289162 64
1788289167 64
1788289172 64
1788289177 64
1788289182 64
1788289187 64
1788289192 64
1788289197 64
1788289202 64
1788289207 64
1788289212 64
```
</details>

---

