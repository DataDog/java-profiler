---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 06:34:10 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 14 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (3 unique values: 16-24 cores)</summary>

```
1790332089 16
1790332094 16
1790332099 16
1790332104 16
1790332110 16
1790332115 16
1790332120 16
1790332125 16
1790332130 16
1790332135 16
1790332140 16
1790332145 16
1790332150 16
1790332155 16
1790332160 16
1790332165 16
1790332170 16
1790332175 24
1790332180 24
1790332185 24
```
</details>

---

