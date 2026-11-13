---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:28:32 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1794572524 31
1794572529 31
1794572534 31
1794572539 31
1794572544 31
1794572549 31
1794572554 31
1794572559 31
1794572564 31
1794572569 31
1794572574 31
1794572580 31
1794572585 31
1794572590 31
1794572595 31
1794572600 31
1794572605 31
1794572610 31
1794572615 31
1794572620 31
```
</details>

---

