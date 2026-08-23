---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-23 00:55:49 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787460702 48
1787460707 43
1787460712 43
1787460717 43
1787460722 43
1787460727 43
1787460732 43
1787460737 43
1787460742 43
1787460747 43
1787460752 43
1787460757 43
1787460762 43
1787460767 43
1787460772 43
1787460777 43
1787460782 43
1787460787 43
1787460792 43
1787460797 43
```
</details>

---

