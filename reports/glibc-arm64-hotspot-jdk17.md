---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 13:59:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 14 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1793123687 44
1793123692 44
1793123697 44
1793123702 44
1793123707 42
1793123712 42
1793123717 42
1793123722 42
1793123727 42
1793123732 42
1793123737 42
1793123742 42
1793123747 44
1793123752 44
1793123757 44
1793123762 44
1793123767 44
1793123772 44
1793123777 44
1793123782 44
```
</details>

---

