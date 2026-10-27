---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 13:59:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793123717 48
1793123722 48
1793123727 48
1793123732 48
1793123737 48
1793123742 48
1793123747 48
1793123752 48
1793123757 48
1793123762 48
1793123767 48
1793123772 48
1793123777 48
1793123782 48
1793123787 48
1793123792 48
1793123797 48
1793123802 48
1793123807 48
1793123812 48
```
</details>

---

