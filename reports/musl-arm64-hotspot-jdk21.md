---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-31 06:39:04 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (4 unique values: 49-64 cores)</summary>

```
1788172465 49
1788172470 49
1788172475 52
1788172480 52
1788172485 52
1788172490 52
1788172495 52
1788172500 52
1788172506 52
1788172511 52
1788172516 52
1788172521 52
1788172526 52
1788172531 52
1788172536 52
1788172541 52
1788172546 52
1788172551 52
1788172556 52
1788172561 52
```
</details>

---

